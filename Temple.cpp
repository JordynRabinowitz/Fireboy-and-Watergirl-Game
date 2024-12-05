// Temple.cpp
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#include "Temple.h"
#include "Fireboy.h"
#include "Watergirl.h"

#include <iostream>
#include <cstdlib>

using namespace std;


/*
creates a temple with water and fire in random spots.
there is a 20% chance a diamond will be hidden at each spot.
*/
Temple:: Temple(){
    // srand(time(0)); MOVED TO MAIN
    for(int r = 0; r < num_rows_; r++){
        int index_fire_water = ((rand() % 11) + 1) + 4; // anywhere between 4 and 15, buttons at 3 or 16
        int fire_or_water = (rand() % 2) + 1;
        for(int c = 0; c < num_cols_; c++){
            if((c == 0 || c == 19) && r != 9){
                temple_data[r][c] = LADDER;
            }
            else if(r % 2 == 0 && c == 3){
                temple_data[r][c] = BUTTON;
            }
            else if(r % 2 == 1 && c == 16){
                temple_data[r][c] = BUTTON;
            }
            else if(r == 9 && c == 6){
                temple_data[r][c] = DOOR;
                c++;
                temple_data[r][c] = FIRE;
                c++;
                temple_data[r][c] = DOOR;
                c++;
                temple_data[r][c] = DOOR;
                c++;
                temple_data[r][c] = WATER;
                c++;
                temple_data[r][c] = DOOR;
            } 
            else if(fire_or_water == 1 && c == index_fire_water && r!=9){
                temple_data[r][c] = FIRE;
                c++;
                temple_data[r][c] = FIRE;
                c++;
                temple_data[r][c] = FIRE;
            }
            else if(fire_or_water == 2 && c == index_fire_water && r!=9){
                temple_data[r][c] = WATER;
                c++;
                temple_data[r][c] = WATER;
                c++;
                temple_data[r][c] = WATER;
            }
            else{
                temple_data[r][c] = WALKWAY;
            }

            int is_diamond = (rand() % 50) + 1;
            if(is_diamond % 5 == 0){
                temple_diamond[r][c] == true;
                num_diamonds++;
            }
            else{
                temple_diamond[r][c] == false;
            }
        }
    }  
}
//sets the position in temple_data to water
void Temple:: setWater(int row, int col){
    temple_data[row][col] = WATER;
}
//sets the position in temple_data to fire
void Temple:: setFire(int row, int col){
    temple_data[row][col] = FIRE;
}
//sets the position in temple_data to a button
void Temple:: setButton(int row, int col){
    temple_data[row][col] = BUTTON;
}
//sets the position in temple_data to a walkway
void Temple:: setWalkway(int row, int col){
    temple_data[row][col] = WALKWAY;
}
//adds a diamond to the num_diamonds
void Temple:: addDiamond(){
    num_diamonds++;
}
//returns the number of rows in the temple
int Temple:: getRows(){
    return num_rows_;
}
//returns the number of columns in the temple
int Temple:: getCols(){
    return num_cols_;
}
//returns the number of diamonds hidden throughout the temple
int Temple:: getNumDiamonds(){
    return num_diamonds;
}
//returns the character at the (row,col) in temple_data
char Temple:: getTempleDataAt(int r, int c){
    return temple_data[r][c];
}

/*
prints the temple and the spot the player is in with F/W
*/
void Temple:: printTemple(int rFireboy, int cFireboy, int rWatergirl, int cWatergirl){
    for(int r = num_rows_ - 1 ; r >= 0; r--){
        for(int c = 0; c < num_cols_; c++){
            if(rFireboy == r && cFireboy == c && rWatergirl == r && cWatergirl == c){
                cout << "FW";
                c++;
            }
            else if(rFireboy == r && cFireboy == c){
                cout << 'F';
            }
            else if(rWatergirl == r && cWatergirl == c){
                cout << 'W';
            }
            else{
                 cout << temple_data[r][c];
            }
        }
        cout << endl;
    }
}


/*
moves fireboy/lavagirl depending on which letter is entered.
if they have no lives left, they cannot be moved
if not valid letter entered prompt to enter new move
if diamond moved onto add to num_diamonds
if button moved onto set the opposites player immunity to true
*/
void Temple:: movePlayers(Fireboy& fb, Watergirl& wg){
    string move;
    cout <<"Fireboy: W = up, S = down, D = right, A = left" << endl;
    cout <<"Watergirl: I = up, K = down, L = right, J = left" << endl;
    cin >> move;

    if(move == "W" && temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == '/' && fb.getFireBoyRow() != 9 && fb.getLives() > 0){
        fb.setFireBoyPosition(fb.getFireBoyRow()+1,fb.getFireBoyCol()); 
        if(isDiamond(fb.getFireBoyRow(), fb.getFireBoyCol())){
            fb.addDiamonds(5);
        }
        if(temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == '~' && fb.getImmunity() == false){
            fb.setLives(fb.getLives() - 1);
            cout << "-1 fireboy life :(. Current fireboy lives: " << fb.getLives() << endl;
        }
        else if(temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == 'o'){
            wg.setImmunity(true);
        }
        else{
            wg.setImmunity(false);
        }   
    }
    else if(move == "S" && (temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == '/' || fb.getFireBoyRow() == 9) && fb.getFireBoyRow() != 0 && fb.getLives() > 0){
        fb.setFireBoyPosition(fb.getFireBoyRow()-1,fb.getFireBoyCol());
        if(isDiamond(fb.getFireBoyRow(), fb.getFireBoyCol())){
            fb.addDiamonds(5);
        }
        if(temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == '~' && fb.getImmunity() == false){
            fb.setLives(fb.getLives() - 1);
            cout << "-1 fireboy life :(. Current fireboy lives: " << fb.getLives() << endl;
        }
        else if(temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == 'o'){
            wg.setImmunity(true);
        }
        else{
            wg.setImmunity(false);
        }
    }
    else if(move == "D" && fb.getFireBoyCol() != 19 && fb.getLives() > 0){
        fb.setFireBoyPosition(fb.getFireBoyRow(), fb.getFireBoyCol()+1);
        if(isDiamond(fb.getFireBoyRow(), fb.getFireBoyCol())){
            fb.addDiamonds(5);
        }
        if(temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == '~' && fb.getImmunity() == false){
            fb.setLives(fb.getLives() - 1);
            cout << "-1 fireboy life :(. Current fireboy lives: " << fb.getLives() << endl;
        }
        else if(temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == 'o'){
            wg.setImmunity(true);
        }
        else{
            wg.setImmunity(false);
        }
    }
    else if(move == "A" && fb.getFireBoyCol() != 0 && fb.getLives() > 0){
        fb.setFireBoyPosition(fb.getFireBoyRow(), fb.getFireBoyCol()-1);
        if(isDiamond(fb.getFireBoyRow(), fb.getFireBoyCol())){
            fb.addDiamonds(5);
        }
        if(temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == '~' && fb.getImmunity() == false){
            fb.setLives(fb.getLives() - 1);
            cout << "-1 fireboy life :(. Current fireboy lives: " << fb.getLives() << endl;
        }
        else if(temple_data[fb.getFireBoyRow()][fb.getFireBoyCol()] == 'o'){
            wg.setImmunity(true);
        }
        else{
            wg.setImmunity(false);
        }
    }
    else if(move == "I" && temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == '/' && wg.getWatergirlRow() != 9 && wg.getLives() > 0){
        wg.setWatergirlPosition(wg.getWatergirlRow()+1, wg.getWatergirlCol());
        if(isDiamond(wg.getWatergirlRow(), wg.getWatergirlCol())){
            wg.addDiamonds(5);
        }
        if(temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == '^' && wg.getImmunity() == false){
            wg.setLives(wg.getLives() - 1);
            cout << "-1 watergirl life :(. Current watergirl lives: " << wg.getLives() << endl;
        }
        else if(temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == 'o'){
            fb.setImmunity(true);
        }
        else{
            fb.setImmunity(false);
        }
    }
    else if(move == "K" && (temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == '/' || wg.getWatergirlRow() == 9) && wg.getWatergirlRow() != 0 && wg.getLives() > 0){
        wg.setWatergirlPosition(wg.getWatergirlRow()-1, wg.getWatergirlCol());
        if(isDiamond(wg.getWatergirlRow(), wg.getWatergirlCol())){
            wg.addDiamonds(5);
        }
        if(temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == '^' && wg.getImmunity() == false){
            wg.setLives(wg.getLives() - 1);
            cout << "-1 watergirl life :(. Current watergirl lives: " << wg.getLives() << endl;
        }
        else if(temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == 'o'){
            fb.setImmunity(true);
        }
        else{
            fb.setImmunity(false);
        }
    }
    else if(move == "J" && wg.getWatergirlCol() != 0 && wg.getLives() > 0){
        wg.setWatergirlPosition(wg.getWatergirlRow(), wg.getWatergirlCol() - 1);
        if(isDiamond(wg.getWatergirlRow(), wg.getWatergirlCol())){
            wg.addDiamonds(5);
        }
        if(temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == '^' && wg.getImmunity() == false){
            wg.setLives(wg.getLives() - 1);
            cout << "-1 watergirl life :(. Current watergirl lives: " << wg.getLives() << endl;
        }
        else if(temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == 'o'){
            fb.setImmunity(true);
        }
        else{
            fb.setImmunity(false);
        }
    }
    else if(move == "L" && wg.getWatergirlCol() != 19 && wg.getLives() > 0){
        wg.setWatergirlPosition(wg.getWatergirlRow(), wg.getWatergirlCol() + 1);
        if(isDiamond(wg.getWatergirlRow(), wg.getWatergirlCol())){
            wg.addDiamonds(5);
        }
        if(temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == '^' && wg.getImmunity() == false){
            wg.setLives(wg.getLives() - 1);
            cout << "-1 watergirl life :(. Current watergirl lives: " << wg.getLives() << endl;
        }
        else if(temple_data[wg.getWatergirlRow()][wg.getWatergirlCol()] == 'o'){
            fb.setImmunity(true);
        }
        else{
            fb.setImmunity(false);
        }
    }
    else{
        if(fb.getLives() == 0){
            cout << "Fireboy DEAD. Cannot move this player. Enter a new move." << endl; 
        }
        else if(wg.getLives() == 0){
            cout << "Watergirl DEAD. Cannot move this player. Enter a new move." << endl; 
        }
        else{
            cout << "Move not valid. Enter a new move." << endl;
            movePlayers(fb, wg);
        }
    }
}

//returns true if fireboy is at his door
bool Temple:: isFireExit(Fireboy& fb){
    if(fb.getFireBoyRow() == 9 && fb.getFireBoyCol() == 7){
        fb.addNumDoorsReached();
        return true;
    }
    else{
        return false;
    }
}
//returns true if wategirl is at her door
bool Temple:: isWaterExit(Watergirl& wg){
    if(wg.getWatergirlRow() == 9 && wg.getWatergirlCol() == 10){
        wg.addNumDoorsReached();
        return true;
    }
    else{
        return false;
    }
}

//returns true if a diamond is at the row, col
bool Temple:: isDiamond(int row, int col){
    if(temple_diamond[row][col]){
        return true;
    }
    else{
        return false;
    }
}

