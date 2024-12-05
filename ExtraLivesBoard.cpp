// ExtraLivesBoard.cpp
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#include <iostream>
#include "Fireboy.h"
#include "Watergirl.h"
#include "ExtraLivesBoard.h"

/*
creates a board with hidden lives in random spots
puts the exit door in the middle
*/
ExtraLivesBoard:: ExtraLivesBoard(){
    player_row = 0;
    player_col = 0;
    num_fire_lives_ = 0;
    num_water_lives_ = 0;
    for(int r = 0; r < num_rows_; r++){ 
        for(int c = 0; c < num_cols_; c++){
            int random_c = (rand() % (50)) + 1;
            int fire_or_water = (rand() % 2) + 1;
            board_data_[r][c] = UNEXPLORED; 
            if(r == 9 && c == 9){
                board_data_[r][c] = DOOR;
                c++;
                board_data_[r][c] = ' ';
                c++;
                board_data_[r][c] = DOOR;
            }
            else if(random_c % 5 == 0){
                if(fire_or_water == 1){
                    hidden_data_[r][c] = FIRELIFE;
                }
                else{
                    hidden_data_[r][c] = WATERLIFE;
                }
            }

        }
    }
}
//returns the row of the player
int ExtraLivesBoard:: getPlayerRow(){
    return player_row;
}
//returns the column of the player
int ExtraLivesBoard:: getPlayerCol(){
    return player_col;
}
//returns the character at (row,col) in board_data_
char ExtraLivesBoard:: getBoardData(int r, int c){
    return board_data_[r][c];
}
//adds the number of fire lives found to Fireboy's lives
void ExtraLivesBoard:: setFireLives(Fireboy& fb){
    fb.setLives(fb.getLives() + num_fire_lives_);
}
//adds the number of water lives found to Watergirl's lives
void ExtraLivesBoard:: setWaterLives(Watergirl& wg){
    wg.setLives(wg.getLives() + num_water_lives_);
}
//sets the player position to (row,col)
void ExtraLivesBoard:: setPlayerPosition(int r, int c){
    player_row = r;
    player_col = c;
}
/*
marks the explored parts of the board as explored
if a life is found add it to the corresponding life found (fire or water) and then unhide it
*/
void ExtraLivesBoard:: setExplored(int r, int c){
    if(hidden_data_[r][c] == FIRELIFE){
        board_data_[r][c] = FIRELIFE;
        num_fire_lives_++;
    }
    else if(hidden_data_[r][c] == WATERLIFE){
        board_data_[r][c] = WATERLIFE;
        num_water_lives_++;
    }
    else{
        board_data_[r][c] = EXPLORED;
    }
}
/*
prints the board and the spot the player is in
*/
void ExtraLivesBoard:: printBoard(){
    for(int r = num_rows_ - 1 ; r >= 0; r--){
        for(int c = 0; c < num_cols_; c++){
            if(player_row == r && player_col == c){
                cout << PLAYER;
            }
            else{
                 cout << board_data_[r][c];
            }
        }
        cout << endl;
    }
}

/*
moves the player depending on which letter they enter and sets the spot to explored
*/
void ExtraLivesBoard:: movePlayer(){
    string move;
    cin >> move;
    if(move == "W" && player_row != 19){
        setPlayerPosition(player_row + 1, player_col);
        setExplored(player_row, player_col);
    }
    else if(move == "S" && player_row != 0){
        setPlayerPosition(player_row - 1, player_col);
        setExplored(player_row, player_col);
    }
    else if(move == "D" && player_col != 19){
        setPlayerPosition(player_row, player_col + 1);
        setExplored(player_row, player_col);
    }
    else if(move == "A" && player_col != 0){
        setPlayerPosition(player_row, player_col - 1);
        setExplored(player_row, player_col);
    }
    else{
        cout << "Move not valid. Enter a new move." << endl;
    }

}

/*
checks if the player is at the exit in player board
*/
bool ExtraLivesBoard::isExit(){
    if(player_row == 9 && player_col == 10){
        return true;
    }
    else{
        return false;
    }
}