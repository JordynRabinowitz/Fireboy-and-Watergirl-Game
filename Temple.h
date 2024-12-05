// Temple.h
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#ifndef TEMPLE_H
#define TEMPLE_H

#include <iostream>
#include "Fireboy.h"
#include "Watergirl.h"

using namespace std;

class Temple{
public:
        Temple(); //Default constructor

        //setters
        void setWater(int row, int col); 
        void setFire(int row, int col);
        void setButton(int row, int col);
        void setWalkway(int row, int col);
        void addDiamond();

        //getters
        char getTempleDataAt(int r, int c);
        int getRows();
        int getCols();
        int getNumDiamonds();

        //other
        void printTemple(int rFireboy, int cFireboy, int rWatergirl, int cWatergirl);
        void movePlayers(Fireboy& fb, Watergirl& wg);
        bool isFireExit(Fireboy& fb);
        bool isWaterExit(Watergirl& wg);
        bool isDiamond(int row, int col);

private:
        static const int num_rows_ = 10; //rows in temple
        static const int num_cols_ = 20; //columns in temple
        char temple_data[num_rows_][num_cols_]; //stores the character that will be displayed at (row, col)
        bool temple_diamond[num_rows_][num_cols_]; //stores the location of hidden diamonds
        int num_diamonds; //stores the number of diamonds in the temple  

        //markers that create the temple
        static const char WATER = '~'; 
        static const char FIRE = '^';
        static const char BUTTON = 'o';
        static const char DIAMOND = '*';
        static const char WALKWAY = '_';
        static const char LADDER = '/';
        static const char DOOR = '|';

};       

#endif

