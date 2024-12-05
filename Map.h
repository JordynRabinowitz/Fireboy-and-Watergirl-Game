// Map.h
// CSCI 1300 Fall 2022
// Editied by: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "Temple.h"

using namespace std;

class Map
{
private:
    const char UNEXPLORED = '-'; // marker for unexplored spaces
    const char EXPLORED = ' ';   // marker for explored spaces
    const char ROOM = 'T';       // marker for Temple locations
    const char DIAMOND = '*';        // marker for diamond locations
    const char FIREBOY = 'F';      // marker for party position
    const char EXIT = 'E';       // marker for exit

    static const int num_rows_ = 12; // number of rows in map
    static const int num_cols_ = 12; // number of columns in map
    static const int max_diamonds_ = 100;  // max diamonds on map
    static const int max_rooms_ = 5; // max number of rooms

    int player_position_[2];              // player position (row,col)
    int dungeon_exit_[2];                 // exit location of the dungeon
    int diamond_positions_[max_diamonds_][3];     // stores the (row,col) positions of diamonds present on map and if they have been found
    int room_positions_[max_rooms_][2];   // stores the (row,col) positions of rooms present on map
    Temple temples[5]; //stores the temples that will be displayed at set positions on the map when the map is created
    char map_data_[num_rows_][num_cols_]; // stores the character that will be shown at a given (row,col)

    int diamond_count_;  // stores number of diamonds currently on map
    int room_count_; // stores number of sites currently on map
public:
    Map();

    void resetMap();

    // getters
    int getPlayerRow();
    int getPlayerCol();
    int getDungeonExitRow();
    int getDungeonExitCol();
    int getRoomCount();
    int getDiamondCount();
    int getNumRows();
    int getNumCols();
    bool isOnMap(int row, int col);
    bool isDiamondLocation(int row, int col);
    bool isRoomLocation(int row, int col);
    bool isExplored(int row, int col);
    bool isFreeSpace(int row, int col);
    bool isDungeonExit(int row, int col);
    Temple getTempleNum(int row, int col);
    Temple getTempleAt(int num);

    // setters
    void setPlayerPosition(int row, int col);
    void setDungeonExit(int row, int col);

    // other
    void displayMap();
    bool move(char);
    bool addDiamond();
    bool addRoom();
    bool removeDiamond(int row, int col);
    bool removeRoom(int row, int col);
    void exploreSpace(int row, int col);
};

#endif