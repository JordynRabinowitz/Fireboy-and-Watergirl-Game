// Fireboy.h
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#ifndef FIREBOY_H
#define FIREBOY_H

#include <iostream>
#include <vector>

using namespace std;

class Fireboy{
public:
        Fireboy(); //Default constructor

        //getters
        int getLives(); 
        char getCharacter();
        vector<int> getDiamonds();
        int getNumDoorsReached();
        bool getImmunity();
        int getFireBoyRow();
        int getFireBoyCol();

        //setters
        void setFireBoyPosition(int r, int c);
        void setLives(int lives_);
        void addDiamonds(int value);
        void addNumDoorsReached();
        void setImmunity(bool immune);
        void resestPosition();

        //other
        int sumPoints();


        
private: 
        const char FIREBOY = 'F'; //marker for Fireboy location
        int lives; //stores number of lives
        vector<int> diamond_points_collected; //stores point value of diamonds collected
        int num_doors_reached; //stores number of doors reached
        bool immunity_to_water; //stores if fireboy can walk through water
        int row; //stores the row fireboy is at
        int col; //stores the column fireboy is at

};
#endif