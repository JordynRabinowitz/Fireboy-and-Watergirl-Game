// Watergirl.h
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#ifndef WATERGIRL_H
#define WATERGIRL_H

#include <iostream>
#include <vector>

using namespace std;

class Watergirl{
public:
        Watergirl(); //Default constructor

        //getters
        int getLives();
        char getCharacter();
        vector<int> getDiamonds();
        int getNumDoorsReached();
        bool getImmunity();
        int getWatergirlRow();
        int getWatergirlCol();

        //setters
        void setWatergirlPosition(int r, int c);
        void setLives(int lives_);
        void addDiamonds(int value);
        void addNumDoorsReached();
        void setImmunity(bool immune);
        void resetPosition();

        //other
        int sumPoints();

        
private: 
        const char WATERGIRL = 'W'; //marker for Fireboy location
        int lives; //stores number of lives
        vector<int> diamond_points_collected; //stores point value of diamonds collected
        int num_doors_reached; //stores number of doors reached
        bool immunity_to_fire; //stores if fireboy can walk through fire
        int row; //stores the row watergirl is at
        int col; //stores the column watergirl is at

};
#endif

