// Fireboy.cpp
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#include "Fireboy.h"
#include <iostream>

using namespace std;

//creates initialized fireboy object
Fireboy:: Fireboy(){
    lives = 0;
    diamond_points_collected.clear();
    num_doors_reached = 0;
    immunity_to_water = false;
    row = 0;
    col = 1;
}
//returns fireboy marker
char Fireboy:: getCharacter(){
    return FIREBOY;
}
//returns lives
int Fireboy:: getLives(){
    return lives;
}
//returns vector of diamonds
vector<int> Fireboy:: getDiamonds(){
    return diamond_points_collected;
}
//returns the number of doors reached
int Fireboy:: getNumDoorsReached(){
    return num_doors_reached;
}
//returns if fireboy can walk through water
bool Fireboy:: getImmunity(){
    return immunity_to_water;
}
//returns player's row
int Fireboy:: getFireBoyRow(){
    return row;
}
//returns player's column
int Fireboy:: getFireBoyCol(){
    return col;
}
//sets the row and column of fireboy
void Fireboy:: setFireBoyPosition(int r, int c){
    row = r;
    col = c;
}
//sets the lives
void Fireboy:: setLives(int lives_){
    lives = lives_;
}
//adds a diamond to the end of the vector
void Fireboy:: addDiamonds(int value){
    diamond_points_collected.push_back(value);
}
//adds to the number of doors reached when a door is reached
void Fireboy:: addNumDoorsReached(){
    num_doors_reached++;
}
//sets the immunity
void Fireboy:: setImmunity(bool immune){
    immunity_to_water = immune;
}
//resets fireboy to its defualt position
void Fireboy:: resestPosition(){
    row = 0;
    col = 1;
}
// calculates fireboy's total points
int Fireboy:: sumPoints(){
    int sum = 0;
    for(int i = 0; i < diamond_points_collected.size(); i++){
        sum += diamond_points_collected.at(i);
    }
    sum += num_doors_reached*5;
    return sum;
}

