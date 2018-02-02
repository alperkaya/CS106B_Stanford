// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "fractals.h"
#include "math.h"
using namespace std;

double const HEIGHT = sqrt(3)/2.0;
void drawTriangle(GWindow& window, double x, double y, double size);
int floodFillRect(GWindow& window, int x, int y, int changeColor, int pixelColor);

void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order) {        
    if(order==0){
        try{
            throw string("Order can not be zero.");
        }catch(string e){
            cout << "Exception Error: " << e << endl;
        }
        return;
    }else if(order<0 || x<0 || y<0 || size<0){
        try{
            throw string("Input values can not be negative.");
        }catch(string e){
            cout << "Exception Error: " << e << endl;
        }
        return;
    }else if(window.inBounds(x, y)){
         try{
             throw string("X and/or Y value is outside of window.");
         }catch(string e){
             cout << "Exception Error: " << e << endl;
         }
         return;
    }

    if(order==1){
        drawTriangle(window,x,y,size);
    }
    order--;
    drawSierpinskiTriangle(window, x, y, size/2.0, order);
    drawSierpinskiTriangle(window, x+(size/2.0), y, size/2.0, order);
    drawSierpinskiTriangle(window, x+(size/4), y+(size/2.0*HEIGHT), size/2.0, order);

}

int floodFill(GWindow& window, int x, int y, int color) {
    if(window.getPixel(x, y)==color){
        return 0;
    }

    return floodFillRect(window, x, y, color, window.getPixel(x, y));
}

void drawTriangle(GWindow& window, double x, double y, double size){
    window.drawLine(x, (y), x+size, (y));
    window.drawLine(x, round(y), x+(size/2.0), (round(y)+(size*HEIGHT)));
    window.drawLine(x+(size/2.0), (y+(size*HEIGHT)), x+size, round(y));
}

/*
//Alternative drawing
void drawTriangle(GWindow& window, double x, double y, double size){
    window.drawPolarLine(x, y, size, 0);
    GPoint point=window.drawPolarLine(x, y, size, -60);
    window.drawPolarLine(point.getX(), point.getY(), size, 60);
}*/

int floodFillRect(GWindow& window, int x, int y, int changeColor, int pixelColor){
    if(window.getPixel(x, y)!=pixelColor){
        return 0;
    }else{
        window.setPixel(x, y, changeColor);
        int result=0;
        result += floodFillRect(window, x+1, y, changeColor, pixelColor);
        result += floodFillRect(window, x-1, y, changeColor, pixelColor);
        result += floodFillRect(window, x, y+1, changeColor, pixelColor);
        result += floodFillRect(window, x, y-1, changeColor, pixelColor);

        return 1+result;
    }

}




