// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include "map.h"
#include "random.h"
using namespace std;

void printIntro();
void getInputFilename(string& filename);
void getNumOfWords(int& numOfWords, const int N);
void getValueN(int& N);
void createNgramMap(Map<Vector<string>, Vector<string> >& ngramMap, string filename, int N);
void adjustWindow(Vector<string>& window, string newWord);
void addToNgramMap(Map<Vector<string>, Vector<string> >& ngramMap, Vector<string>& window, string newWord);
void printNgramMap(const Map<Vector<string>, Vector<string> >& ngramMap);
void pickStartingWindow(const Map<Vector<string>, Vector<string> >& ngramMap, Vector<string>& startingWindow);
void generateRandomText(Map<Vector<string>, Vector<string> >& ngramMap, Vector<string>& startingWindow, int numOfWords);
string chooseWord(Vector<string>& windowValue);

int main() {

    printIntro();
    int N, numOfWords;
    string filename="";
    Map<Vector<string>, Vector<string> > ngramMap;
    Vector<string> startingWindow;
    getInputFilename(filename);
    getValueN(N);
    cout << endl;
    createNgramMap(ngramMap, filename, N);
    while(1){
        getNumOfWords(numOfWords, N);
        if(numOfWords!=0){
            pickStartingWindow(ngramMap, startingWindow);
            generateRandomText(ngramMap, startingWindow, numOfWords);
        }else{
            break;
        }
    }
    cout << "Exiting." << endl;
    return 0;
}

void printIntro(){
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups " << endl;
    cout << "of words, and I'll create random text for you. " << endl;
    cout << endl;
}

void getInputFilename(string& filename){
    getLine("Input file name? ", filename);
    while(!fileExists(filename)){
        cout << "Unable to open that file.  Try again." << endl;
        getLine("Input file name? ", filename);
    }
}

void getNumOfWords(int& numOfWords, int N){
    while(1){
        numOfWords=getInteger("# of random words to generate (0 to quit)? ", "Illegal integer format. Try again.");
        if(numOfWords==0){
            return;
        }else if(numOfWords<N){
            cout << "Must be at least "<< N << " words." << endl << endl;
        }else{
            return;
        }
    }

}

void getValueN(int& N){
    N=getInteger("Value of N?", "");
    while(N<2){
        cout << "N must be 2 or greater." << endl;
        N=getInteger("Value of N?", "");
    }
}

void createNgramMap(Map<Vector<string>, Vector<string> >& ngramMap, string filename, int N){
    int windowSize=N-1;
    string newWord;
    Vector<string> window;
    Vector<string> windowHead;

    ifstream ifs;
    ifs.open(filename);

    while(ifs.good()){
        ifs >> newWord;        
        if(window.size()<windowSize){
            window.add(newWord);
            windowHead=window;
        }else if(window.size()==windowSize){
            addToNgramMap(ngramMap, window, newWord);
            adjustWindow(window, newWord);
        }
    }

    //make circular
    for(int i=0; i<N-1; i++){
        string windowheadKey=windowHead.get(i);
        addToNgramMap(ngramMap, window, windowheadKey);
        adjustWindow(window, windowheadKey);
    }

    //printNgramMap(ngramMap);

    ifs.close();
}

void adjustWindow(Vector<string>& window, string newWord){
    window.remove(0);
    window.add(newWord);    
}

void addToNgramMap(Map<Vector<string>, Vector<string> >& ngramMap, Vector<string>& window, string newWord){
    Vector<string> windowValue=ngramMap.get(window);
    windowValue.add(newWord);
    ngramMap.add(window, windowValue);    
}

void printNgramMap(const Map<Vector<string>, Vector<string> >& ngramMap){
    for(Vector<string> key:ngramMap){
        int counter=0;
        cout << "{ " ;
        while(counter<key.size()){
            cout << key.get(counter) << ", ";
            counter++;
        }
        cout << "} " ;
        cout << "\t";
        cout << ": ";
        cout << "{ " ;
        Vector<string> value=ngramMap[key];
        counter=0;
        while(counter<value.size()){
            cout << value.get(counter) << ", ";
            counter++;
        }
        cout << "} " ;
        cout << ", " ;
        cout << endl;
    }
}

void pickStartingWindow(const Map<Vector<string>, Vector<string> >& ngramMap, Vector<string>& startingWindow){
    int randomIdx=randomInteger(0, ngramMap.size()-1);
    startingWindow=ngramMap.keys().get(randomIdx);
}

void generateRandomText(Map<Vector<string>, Vector<string> >& ngramMap, Vector<string>& startingWindow, int numOfWords){
    cout << "... ";
    for(int i=0; i<startingWindow.size(); i++){
        cout << startingWindow.get(i) << " ";
    }
    numOfWords -= startingWindow.size();
    while(1){
        Vector<string> windowValue=ngramMap.get(startingWindow);
        string value=chooseWord(windowValue);
        adjustWindow(startingWindow, value);
        cout << value << " ";

        numOfWords--;
        if(numOfWords<=0){
            break;
        }
    }
    cout << "..." << endl << endl;
}

string chooseWord(Vector<string>& windowValue){
    if(windowValue.size()==1){
        return windowValue.get(0);
    }else if(windowValue.size()==0){
        cout << "====================";
    }else{
        int _r=randomInteger(0, windowValue.size()-1);
        return windowValue.get(_r);
    }
}
