// ExtraLivesBoard.h
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins

#ifndef EXTRALIVESBORAD_H
#define EXTRALIVESBOARD_H

#include <iostream>
#include "Fireboy.h"
#include "Watergirl.h"
using namespace std;

class ExtraLivesBoard{
public: 
        ExtraLivesBoard(); //Default constructor

        //Getters
        int getPlayerRow();
        int getPlayerCol();
        char getBoardData(int r, int c);

        //Setters
        void setFireLives(Fireboy& fb);
        void setWaterLives(Watergirl& wg);
        void setPlayerPosition(int r, int c);
        void setExplored(int r, int c);

        //other
        void printBoard();
        void movePlayer();
        bool isExit();

private:
        //markers that create the board
        const char EXPLORED = ' ';
        const char UNEXPLORED = '-';
        const char PLAYER = 'X';
        const char FIRELIFE = 'F';
        const char WATERLIFE = 'W';
        const char DOOR = '|';

        int num_fire_lives_; //number of fire lives collected
        int num_water_lives_; //number of water lives collected
        static const int num_rows_ = 20; //number of rows in board
        static const int num_cols_ = 20; //number of columns in board
        int player_row; //stores the row the player is at
        int player_col; //stores the column the player is at
        char board_data_[num_rows_][num_cols_]; //stores the character that will be displayed at (row,col)
        char hidden_data_[num_rows_][num_cols_]; //stores the location of hidden lives
};

#endif