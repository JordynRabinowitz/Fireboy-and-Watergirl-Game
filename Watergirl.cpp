// Watergirl.cpp
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#include "Watergirl.h"
#include <iostream>

using namespace std;

//creates initialized watergirl object
Watergirl::Watergirl(){
    lives = 0;
    diamond_points_collected.clear();
    num_doors_reached = 0;
    immunity_to_fire = false;
    row = 0;
    col = 2;
}
//returns watergirl marker
char Watergirl:: getCharacter(){
    return WATERGIRL;
}
//returns lives
int Watergirl:: getLives(){
    return lives;
}
//returns vector of diamonds
vector<int> Watergirl:: getDiamonds(){
    return diamond_points_collected;
}
//returns the number of doors reached
int Watergirl:: getNumDoorsReached(){
    return num_doors_reached;
}
//returns if fireboy can walk through fire
bool Watergirl:: getImmunity(){
    return immunity_to_fire;
}
//returns player's row
int Watergirl:: getWatergirlRow(){
    return row;
}
//returns player's column
int Watergirl:: getWatergirlCol(){
    return col;
}
//sets the row and column of watergirl
void Watergirl:: setWatergirlPosition(int r, int c){
    row = r;
    col = c;
}
//sets the lives
void Watergirl:: setLives(int lives_){
    lives = lives_;
}
//adds a diamond to the end of the vector
void Watergirl:: addDiamonds(int value){
    diamond_points_collected.push_back(value);
}
//adds to the number of doors reached when a door is reached
void Watergirl:: addNumDoorsReached(){
    num_doors_reached++;
}
//sets the immunity
void Watergirl:: setImmunity(bool immune){
    immunity_to_fire = immune;
}
//resets watergirl to its defualt position
void Watergirl:: resetPosition(){
    row = 0;
    col = 2;
}
// calculates watergirl's total points
int Watergirl:: sumPoints(){
    int sum = 0;
    for(int i = 0; i < diamond_points_collected.size(); i++){
        sum += diamond_points_collected.at(i);
    }
    sum += num_doors_reached*5;
    return sum;
}