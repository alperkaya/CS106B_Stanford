// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include "set.h"
#include <locale>
#include "queue.h"

using namespace std;

void printIntro();
void loadDictionary(Set<string>& dictionary);
bool getUserWord(string& word1, string& word2, const Set<string>& dictionary);
void findNeighbour(string word, const Set<string>& dictionary, Set<string>& neighbours);
void wordLadder(string w1, string w2, const Set<string>& dictionary);
bool checkWordExistInDictionary(string word, const Set<string>& dictionary);

int main() {
    printIntro();
    Set<string> dictionary;
    loadDictionary(dictionary);
    string word1="";
    string word2="";

    while(1){
        while(!getUserWord(word1, word2, dictionary)){
            cout << endl;
        }
        if(word1.empty() || word2.empty()){
            break;
        }

        wordLadder(word1, word2, dictionary);
        cout<<endl;
    }


    cout << "Have a nice day." << endl;
    return 0;
}

void printIntro(){
    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the " << endl;
    cout << "first into the second by modifying one letter at a time. " << endl;
    cout << endl;
}

void loadDictionary(Set<string>& dictionary){
    string filename="";
    string word="";
    ifstream ifs;

    getLine("Dictionary file name: ", filename);
    while(!fileExists(filename)){
        cout << "Unable to open that file.  Try again." << endl;
        getLine("Dictionary file name: ", filename);
    }
    cout << endl;

    ifs.open(filename);

    while(ifs.good()){
        getline(ifs,word);
        dictionary.add(word);
    }

    ifs.close();
}

bool getUserWord(string& word1, string& word2, const Set<string>& dictionary){
    word1=getLine("Word 1 (or Enter to quit): ");
    if(word1.empty()){
        return true;
    }
    word2=getLine("Word 2 (or Enter to quit): ");
    if(word2.empty()){
        return true;
    }

    if(word1==word2){
        cout << "The two words must be different." << endl;
        return false;
    }else if(word1.size()!=word2.size()){
        cout << "The two words must be the same length." << endl;
        return false;
    }else{
        word1=toLowerCase(word1);
        word2=toLowerCase(word2);

        if(!checkWordExistInDictionary(word1, dictionary) || !checkWordExistInDictionary(word2, dictionary)){
                cout << "The two words must be found in the dictionary." << endl;
                return false;
        }

        return true;
    }
}

bool checkWordExistInDictionary(string word, const Set<string>& dictionary){
    return dictionary.contains(word);
}

void findNeighbour(string word, const Set<string>& dictionary, Set<string>& neighbours){
    string _w=word;
    for(int i=0; i<_w.length(); i++){
        for(char c='a'; c<='z'; c++){
            _w[i]=c;            
            if(dictionary.contains(_w)){                
                neighbours.add(_w);
            }
        }
        _w=word;
     }
}

void wordLadder(string w1, string w2, const Set<string>& dictionary){
    Set<string> newNeighbours;
    Set<string> usedNeighbours;

    Queue<Stack<string> > qs;
    Stack<string> s;
    s.push(w1);
    qs.enqueue(s);

    while(!qs.isEmpty()){
        Stack<string> __s=qs.dequeue();
        if(__s.peek()==w2){
            cout << "A ladder from data back to code:" << endl;
            while(!__s.isEmpty())
                cout << __s.pop() << " ";
            cout << endl;
            return;
        }
        findNeighbour(__s.peek(), dictionary, newNeighbours);

        while(newNeighbours.size()>0){
            string item=newNeighbours.first();
            if(!usedNeighbours.contains(item)){
               Stack<string> s2=__s;
               s2.push(item);               
               usedNeighbours.add(item);
               qs.add(s2);
            }
            newNeighbours.remove(item);
        }
        newNeighbours.clear();
    }


    cout << "No word ladder found from " << w2 << " back to " << w1;
    cout << endl;
    return;


}
