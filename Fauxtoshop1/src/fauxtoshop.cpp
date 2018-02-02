// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: rewrite this comment

#include <iostream>
#include "simpio.h"
#include "console.h"
#include "gbufferedimage.h"
#include "grid.h"
#include "gwindow.h"
#include "fauxtoshop-provided.h"   // instructor-provided code
using namespace std;

bool loadImage(GBufferedImage& img);
void imgScatter(GBufferedImage& img, Grid<int>& gridImg, int degree);
void edgeDetect(GBufferedImage& img, Grid<int>& gridImg, int threshold);
void greenScreenEffect(GBufferedImage& img, Grid<int>& gridImg, Grid<int>&  stickerImg, int tolerance, int row, int col);
void diffImages(const GBufferedImage& img, const GBufferedImage& secondImg, const GWindow& gw);
void saveImage(GBufferedImage &img);
void printImageFilters();
int getValue(string prompt, int maxValue);

int main() {

    // basic setup of Graphics Window
    GWindow gw;
    gw.setTitle("Fauxtoshop");
    gw.setExitOnClose(true);
    gw.setVisible(true);
    cout << "Welcome to Fauxtoshop!" << endl;

    while(true){
        GBufferedImage img;
        if(!loadImage(img))
            break;

        gw.setCanvasSize(img.getWidth(), img.getHeight());
        gw.add(&img, 0, 0);
        Grid<int> gridOrgImg = img.toGrid();

        printImageFilters();

        int filterChoice = getValue("Your Choice: ", 4);

        switch(filterChoice){
        case 1:
        {
            int degree=getValue("Enter degree of scatter[1-100] :", 100);
            imgScatter(img, gridOrgImg, degree);
            saveImage(img);
            break;
        }
        case 2:
        {
            int threshold=0;
            while(threshold<=0){
                cout << "Enter threshold for edge detection [1-100] : ";
                threshold=getInteger();
            }
            edgeDetect(img, gridOrgImg, threshold);
            saveImage(img);
            break;
        }
        case 3:
        {
            cout << "Now choose another pic to add " << endl;
            cout << "Enter name of image file to open: " ;
            GBufferedImage stickerImg;
            string stickerName;
            //cin >> stickerName;
            getline(cin, stickerName);
            while(!openImageFromFilename(stickerImg, stickerName)){
                cout << "Enter name of image file to open: " ;
                getline(cin, stickerName);
            }

            int tolerance=getValue("Enter threshold for edge detection [1-100] : ", 100);

            int row=-1, col=-1;
            while(row<0 || col<0 || row>gridOrgImg.numRows() || col>gridOrgImg.numCols()){
                cout << "Enter location to place image as \" (row,col) \" (or blank to use mouse): ";

                string s_row_col_value;
                getline(cin, s_row_col_value);

                if(s_row_col_value != ""){
                    stringstream row_col_value(s_row_col_value);
                    char exp;
                    row_col_value >> exp >> row >> exp >> col >> exp;
                }else{
                    getMouseClickLocation(row, col);
                }

            }

            Grid<int> gridSticker = stickerImg.toGrid();
            greenScreenEffect(img, gridOrgImg, gridSticker, tolerance, row, col);
            saveImage(img);
            break;
        }
        case 4:
        {
            cout << "Now choose another image file to compare to. " << endl;
            cout << "Enter name of image file to open: " ;
            GBufferedImage diffImg;
            string stickerName;
            getline(cin, stickerName);
            cout << "Opening image file, may take a minute..." << endl;
            while(!openImageFromFilename(diffImg, stickerName)){
                cout << "Enter name of image file to open: " ;
                getline(cin, stickerName);
            }
            diffImages(img, diffImg, gw);


        }
        }

        cout << endl;
        img.clear();
        gw.clear();

    }

    // uncomment this if you want the same random numbers on each run
    fakeRandomNumberGenerator();

    // TODO: finish the program!
    cout << "Exiting." << endl;
    return 0;
}

void greenScreenEffect(GBufferedImage& img, Grid<int>& gridOrgImg, Grid<int>& gridStickerImg, int tolerance, int row, int col){
    int refRed=0, refGreen=0, refBlue=0;
    GBufferedImage::getRedGreenBlue(GREEN, refRed, refGreen, refBlue);

    for(int r=0; r<gridStickerImg.numRows(); r++){
        for(int c=0; c<gridStickerImg.numCols(); c++){
            int red=0, green=0, blue=0;
            GBufferedImage::getRedGreenBlue(gridStickerImg[r][c], red, green, blue);

            if(gridOrgImg.inBounds(col+c, row+r)){
                if(max(max(abs(red-refRed), abs(green-refGreen)), abs(blue-refBlue)) > tolerance){
                    gridOrgImg[row+r][col+c]=GBufferedImage::createRgbPixel(red, green, blue);
                }
            }

        }
    }
    img.fromGrid(gridOrgImg);
}

void edgeDetect(GBufferedImage& img, Grid<int>& gridOrgImg, int threshold){
    Grid<int> copyImg = gridOrgImg;
    for(int r=0; r<gridOrgImg.numRows(); r++){
        for(int c=0; c<gridOrgImg.numCols(); c++){
            int red=0, green=0, blue=0;
            GBufferedImage::getRedGreenBlue(gridOrgImg[r][c], red, green, blue);

            int black=0;
            for(int chosenRow=r-1; chosenRow<=r+1; chosenRow++){
                for(int chosenCol=c-1; chosenCol<=c+1; chosenCol++){
                    if(img.inBounds(chosenCol, chosenRow)){
                        int refRed=0, refGreen=0, refBlue=0;
                        GBufferedImage::getRedGreenBlue(gridOrgImg[chosenRow][chosenCol], refRed, refGreen, refBlue);
                        if(max(max(abs(red-refRed), abs(green-refGreen)), abs(blue-refBlue)) > threshold)
                            black=1;
                    }
                }
            }
            if(black==1)
                copyImg[r][c] = BLACK;
            else
                copyImg[r][c] = WHITE;

        }
    }
    img.fromGrid(copyImg);
}

void imgScatter(GBufferedImage& img, Grid<int>& gridOrgImg, int degree){

    Grid<int> gridImg = gridOrgImg;
    for(int r=0; r<gridImg.numRows(); r++){
        for(int c=0; c<gridImg.numCols(); c++){
            int red=0, green=0, blue=0;
            int randomRow = -1;
            int randomCol = -1;

            while(!img.inBounds(randomCol, randomRow)){
                randomRow = randomInteger(r-degree, r+degree);
                randomCol = randomInteger(c-degree, c+degree);
            }

            GBufferedImage::getRedGreenBlue(gridImg[randomRow][randomCol], red, green, blue);
            gridImg[r][c] = GBufferedImage::createRgbPixel(red, green, blue);
        }
    }

    img.fromGrid(gridImg);

}

bool loadImage(GBufferedImage& img){
    cout << "Enter name of image file to open (or blank to quit) : ";
    string filename;
    getline(cin, filename);

    if(filename.empty()){
        return false;
    }

    cout << "Opening image file, may take a minute..." << endl;

    while(!openImageFromFilename(img, filename)){
        cout << "Enter name of image file to open (or blank to quit) : ";
        getline(cin, filename);

        if(filename.empty()){
            return false;
        }
    }

    return true;
}

void printImageFilters(){
    cout << "Which image filter would you like to apply?" << endl;
    cout << "   1 - Scatter" << endl;
    cout << "   2 - Edge Detection" << endl;
    cout << "   3 - \"Green Screen\" with another image" << endl;
    cout << "   4 - Compare image with another image" << endl;
}

void diffImages(const GBufferedImage& firstImg, const GBufferedImage& secondImg, const GWindow& gw){
    int diffPixels = firstImg.countDiffPixels(secondImg);

    if(diffPixels==0){
        cout << "These images are the same!" << endl;
    }else{
        cout << "These images differ in " << diffPixels << " pixel locations!" << endl;
        showDiffWindow(gw, secondImg.getFilename());
    }
}

void saveImage(GBufferedImage& img){
    cout << "Enter filename to save image(blank to skip saving): ";
    string fileNameToSave="";
    getline(cin, fileNameToSave);
    if(fileNameToSave != ""){
        while(!saveImageToFilename(img, fileNameToSave)){
            getline(cin, fileNameToSave);

            if(fileNameToSave == ""){
                break;
            }
        }
    }
}

int getValue(string prompt, int maxValue){
    int value=-1;
    while(value<1 || value>maxValue){
        value = getInteger(prompt);
    }

    return value;
}
