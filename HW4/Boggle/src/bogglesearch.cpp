#include <string>
#include "grid.h"
#include "lexicon.h"
#include "set.h"
#include "vector.h"
#include "shuffle.h"
#include "bogglegui.h"
#include "queue.h"
using namespace std;

int calculatePoints(const string& word);
bool wordSearch(const Grid<char>& board, int& row, int& col, Set<int>& elements, const string& word, int count=0);
void doComputerWordSearch(const Grid<char>& board, int& row, int& col, string& word, Set<int>& elements, Set<string>& searchResults, const Lexicon& dictionary, const Set<string>& humanWords);

Grid<char> generateRandomBoard(int size, const Vector<std::string>& letterCubes) {
    Vector<string> letCubes = letterCubes;
    for(int i=0; i<letCubes.size(); i++){
        string letters=letCubes.get(i);
        string temp=shuffle(letters);
        letCubes.remove(i);
        letCubes.add(temp);
    }
    shuffle(letCubes);

    Grid<char> board(size,size);
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            string cube=letCubes.get(i*size+j);
            board[i][j]=cube[0];
        }
    }
    return board;
}

bool humanWordSearch(const Grid<char>& board, const Lexicon& dictionary, const string& word) {
    if(!dictionary.contains(word) || word.size()<BoggleGUI::MIN_WORD_LENGTH){
        return false;
    }

    BoggleGUI::setAnimationDelay(100);
    Set<int> elements;
    BoggleGUI::clearHighlighting();

    for(int r=0; r<board.numRows(); r++){
        for(int c=0; c<board.numCols(); c++){
            BoggleGUI::setHighlighted(r, c, true, true);
            if(board[r][c]==word.front()){
                if(wordSearch(board, r, c, elements, word)){
                    BoggleGUI::scorePointsHuman(calculatePoints(word));
                    return true;
                }
            }
            BoggleGUI::setHighlighted(r, c, false, true);
        }
    }
    return false;
}

bool wordSearch(const Grid<char>& board, int row, int col, Set<int>& elements, const string& word, int count){
    if(count==word.size()){
        elements.clear();
        return true;
    }else if(!board.inBounds(row,col)){
        return false;
    }

    BoggleGUI::setHighlighted(row, col,true,true);

    if(board[row][col]==word[count] && !elements.contains(row*board.numCols()+ col)){
        elements.add(row*board.numCols()+ col);
        if(wordSearch(board, row-1, col-1, elements, word, count+1) ||
           wordSearch(board, row-1, col, elements, word, count+1)   ||
           wordSearch(board, row-1, col+1, elements, word, count+1) ||
           wordSearch(board, row, col-1, elements, word, count+1)   ||
           wordSearch(board, row, col+1, elements, word, count+1)   ||
           wordSearch(board, row+1, col-1, elements, word, count+1) ||
           wordSearch(board, row+1, col, elements, word, count+1)   ||
           wordSearch(board, row+1, col+1, elements, word, count+1)){
           return true;
        }
        elements.remove(row*board.numCols()+ col);
    }

    if(!elements.contains(row*board.numCols()+ col)){
        BoggleGUI::setHighlighted(row, col,false,true);
    }

    return false;
}

Set<string> computerWordSearch(const Grid<char>& board, const Lexicon& dictionary, const Set<string>& humanWords) {
    Set<string> computerWords;
    Set<int> elements;
    string word="";

    // visit every cell in grid
    for(int r=0; r<board.numRows(); r++){
        for(int c=0; c<board.numCols(); c++){
            doComputerWordSearch(board, r, c, word, elements, computerWords, dictionary, humanWords);
        }
    }

    // calculate total points
    int points=0;
    for(string w : computerWords){
        points+=calculatePoints(w);
    }
    BoggleGUI::scorePointsComputer(points);

    return computerWords;
}

void doComputerWordSearch(const Grid<char>& board, int row, int col, string& word, Set<int>& elements, Set<string>& searchResults, const Lexicon& dictionary, const Set<string>& humanWords){
    // check if it is out of border
    if(!board.inBounds(row,col)){
        return;
    }

    // current board[row][col] never used for this case then start to use
    if(!elements.contains(row*board.numCols()+ col)){
        word+=board[row][col];
        elements.add(row*board.numCols()+ col);
    }else{
        // current board[row][col] has been used
        return;
    }

    //prune tree
    if(dictionary.containsPrefix(word)){
        if(!humanWords.contains(word) && dictionary.contains(word) && word.size()>=BoggleGUI::MIN_WORD_LENGTH){
            searchResults.add(word);
        }

        doComputerWordSearch(board, row-1, col-1, word, elements, searchResults, dictionary, humanWords);
        doComputerWordSearch(board, row-1, col,   word, elements, searchResults, dictionary, humanWords);
        doComputerWordSearch(board, row-1, col+1, word, elements, searchResults, dictionary, humanWords);
        doComputerWordSearch(board, row,   col-1, word, elements, searchResults, dictionary, humanWords);
        doComputerWordSearch(board, row,   col+1, word, elements, searchResults, dictionary, humanWords);
        doComputerWordSearch(board, row+1, col-1, word, elements, searchResults, dictionary, humanWords);
        doComputerWordSearch(board, row+1, col,   word, elements, searchResults, dictionary, humanWords);
        doComputerWordSearch(board, row+1, col+1, word, elements, searchResults, dictionary, humanWords);
    }

    // backtrack
    word.pop_back();
    elements.remove(row*board.numCols()+ col);

}

int calculatePoints(const string& word){
    if(word.length()==5){
        return 2;
    }else if(word.length()==6){
        return 3;
    }else if(word.length()==7){
        return 5;
    }else if(word.length()>7){
        return 11;
    }

    return 1;
}
