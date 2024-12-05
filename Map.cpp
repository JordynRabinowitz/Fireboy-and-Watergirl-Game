// Map.cpp
// CSCI 1300 Fall 2022
// Editied by: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#include "Map.h"
#include "Temple.h"
#include <cstdlib>

using namespace std;

Map::Map()
{   
    resetMap();
}

/*
 * Algorithm: Resets positions of player, diamonds and rooms and clears map_data_
 * Set Player position coordinates to 0
 * Set diamond_count_ to false
 * Set room_count_ to 0
 * loop i from 0 to max_diamonds_
 *      Set row and col of location to -1
 * loop i from 0 to max_rooms
 *      Set row and col of room location to -1
 * loop i from 0 to num_rows_
 *      loop j from 0 to num_cols_
 *          Set (i,j) location on map_data_ to '-'
 * Parameters: none
 * Return: nothing (void)
 */
void Map::resetMap()
{
    // resets player position, count values, and initializes values in position arrays to -1
    player_position_[0] = 0;
    player_position_[1] = 0;

    // set dungeon exit
    dungeon_exit_[0] = num_rows_ - 1;
    dungeon_exit_[1] = num_cols_ / 2;

    for (int i = 0; i < max_diamonds_; i++)
    {
        diamond_positions_[i][0] = -1;
        diamond_positions_[i][1] = -1;
    }
    diamond_count_ = 0;

    for (int i = 0; i < max_rooms_; i++)
    {
        room_positions_[i][0] = -1;
        room_positions_[i][1] = -1;
    }
    room_count_ = 0;

    for (int i = 0; i < num_rows_; i++)
    {
        for (int j = 0; j < num_cols_; j++)
        {
            map_data_[i][j] = UNEXPLORED;
        }
    }
    map_data_[dungeon_exit_[0]][dungeon_exit_[1]] = EXIT;
}

// return player's row position
int Map::getPlayerRow()
{
    return player_position_[0];
}

// return player's column position
int Map::getPlayerCol()
{
    return player_position_[1];
}

// return current room count
int Map::getRoomCount()
{
    return room_count_;
}

// return dungeon exit row
int Map::getDungeonExitRow()
{
    return dungeon_exit_[0];
}

// return dungeon exit col
int Map::getDungeonExitCol()
{
    return dungeon_exit_[1];
}

// set player position, if in range
void Map::setPlayerPosition(int row, int col)
{
    if (isOnMap(row, col))
    {
        player_position_[0] = row;
        player_position_[1] = col;
    }
}

// set dungeon exit position, if in range
void Map::setDungeonExit(int row, int col)
{
    if (isOnMap(row, col))
    {
        dungeon_exit_[0] = row;
        dungeon_exit_[1] = col;
    }
}

// returns member variable num_rows_
int Map::getNumRows()
{
    return num_rows_;
}

// returns member variable num_cols_
int Map::getNumCols()
{
    return num_cols_;
}

/*
 * @brief Checks if the given (row, col) position is on the map
 *
 * Algorithm:
 *  if 0 <= row < num_rows_ and 0 <= col < num_cols_:
 *      return true
 *  else:
 *      return false
 *
 * Parameters: row (int), col (int)
 * Returns: bool
 */
bool Map::isOnMap(int row, int col)
{
    if (0 <= row && row < num_rows_ && 0 <= col && col < num_cols_)
    {
        return true;
    }
    return false;
}

/*
 * Algorithm: Checks if the location is an diamond location
 * if (row, col) is not within the map boundaries
 *      return false
 * loop i from 0 to diamond_count_
 *      if (row,col) is a diamond location
 *          return true
 * return true
 * Parameters: row (int), col (int)
 * return false
 * Parameters: none
 * Return: boolean (bool)
 */
bool Map::isDiamondLocation(int row, int col)
{
    if (!isOnMap(row, col))
    {
        return false;
    }
    for (int i = 0; i < diamond_count_; i++)
    {
        if (row == diamond_positions_[i][0] && col == diamond_positions_[i][1])
        {
            return true;
        }
    }
    return false;
}

/*
 * Algorithm: Checks if the location is an room location
 * if (row, col) is not within the map boundaries
 *      return false
 * loop i from 0 to room_count_
 *      if (row,col) is a room location
 *          return true
 * return true
 * Parameters: row (int), col (int)
 * return false
 * Parameters: none
 * Return: boolean (bool)
 */
bool Map::isRoomLocation(int row, int col)
{
    if (!isOnMap(row, col))
    {
        return false;
    }
    for (int i = 0; i < room_count_; i++)
    {
        if (row == room_positions_[i][0] && col == room_positions_[i][1])
        {
            return true;
        }
    }
    return false;
}

/*
 * Algorithm: Checks if the given row and column is an explored space
 * if (row, col) is not on the map:
 *     return false
 * if map_data_[row][col] is ' ':
 *     return true
 * if (row, col) is diamond location and has been found:
 *     return true
 * else:
 *     return false
 */
bool Map::isExplored(int row, int col)
{
    if (!isOnMap(row, col))
    {
        return false;
    }
    if (map_data_[row][col] == EXPLORED)
    {
        return true;
    }
    for (int i = 0; i < diamond_count_; i++)
    {
        if (diamond_positions_[i][0] == row && diamond_positions_[i][1] == col)
        {
            if (diamond_positions_[i][2] == true)
            {
                return true;
            }
            break;
        }
    }
    return false;
}

/*
 * Algorithm: checks if (row, col) is dungeon_exit_
 *
 */
bool Map::isDungeonExit(int row, int col)
{
    if (row == dungeon_exit_[0] && col == dungeon_exit_[1])
    {
        return true;
    }
    return false;
}

/*
 * Algorithm: Checks if the given row and column on map is a free space
 * if row and column is not within the map boundaries
 *      return false
 * if row and column is a npc location
 *      return false
 * if row and column is a room location
 *      return false
 * if row and column is the dungeon exit
 *      return false
 * return true
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::isFreeSpace(int row, int col)
{
    if (!isOnMap(row, col))
    {
        return false;
    }
    if (isDiamondLocation(row, col))
    {
        return false;
    }
    if (isRoomLocation(row, col))
    {
        return false;
    }
    if (isDungeonExit(row, col))
    {
        return false;
    }
    return true;
}

/*
 * Algorithm: Create a diamond on the map at a random position
 * if diamond is present on map
 *      return false
 * if (row,col) is not a free space
 *      return false
 * store row and col values in diamondPosition array
 * mark diamond as hidden
 * set (row,col) value in map_data_ to '*'
 * increment diamond_count_
 * return true
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::addDiamond()
{
    int row = (rand() % 11) + 1;
    int col = (rand() % 11) + 1;

    if (diamond_count_ >= max_diamonds_)
    {
        return false;
    }
    if (!isFreeSpace(row, col))
    {
        return false;
    }

    diamond_positions_[diamond_count_][0] = row;
    diamond_positions_[diamond_count_][1] = col;
    diamond_positions_[diamond_count_][2] = false;
    map_data_[row][col] = DIAMOND;
    diamond_count_++;
    return true;
}

/*
 * Algorithm: Create a room on the map at a random position
 * if room_count_ is more than or equal to number of rooms
 *      return false
 * if (row,col) is not a free space
 *      return false
 * if next row in room_positions_ matrix is -1 -1
 *      store row, col and type values in the current row of room_positions_ matrix
 *      adds new temple to temples array
 *      increment room_count_
 *      Set (row,col) value in map_data_ to 'R'
 *      return true
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::addRoom()
{   
    int row = (rand() % 12) + 1;
    int col = (rand() % 12) + 1;

    if (room_count_ >= max_rooms_)
    {
        return false;
    }

    // location must be blank to spawn
    if (!isFreeSpace(row, col))
    {
        return false;
    }
    room_positions_[room_count_][0] = row;
    room_positions_[room_count_][1] = col;
    // srand(time(0)); MOVED TO MAIN
    Temple new_temple = Temple();
    temples[room_count_] = new_temple;
    room_count_++;
    map_data_[row][col] = ROOM;
    return true;
}

/*
 * Algorithm: Removes the diamond at (row, col) from the map
 * loop i from 0 to diamond_count_
 *      if diamond_position[i] is (row, col)
 *          swap diamond_position[diamond_count_-1] with diamond_position[i]
 *          reset diamond_position[diamond_count_-1][0] and diamond_position[diamond_count_-1][1] to -1
 *          reset diamond_position[diamond_count_-1][2] to 0
 *          decrement diamond_count_
 *          set map data at (row, col) to explored
 *          return true
 * return false
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::removeDiamond(int row, int col)
{
    for (int i = 0; i < diamond_count_; i++)
    {
        if (diamond_positions_[i][0] == row && diamond_positions_[i][1] == col)
        {
            // swap i'th diamond with last diamond
            diamond_positions_[i][0] = diamond_positions_[diamond_count_ - 1][0];
            diamond_positions_[i][1] = diamond_positions_[diamond_count_ - 1][1];
            diamond_positions_[i][2] = diamond_positions_[diamond_count_ - 1][2];
            // reset last diamond
            diamond_positions_[diamond_count_ - 1][0] = -1;
            diamond_positions_[diamond_count_ - 1][1] = -1;
            diamond_positions_[diamond_count_ - 1][2] = false;
            // decrement diamond_count_
            diamond_count_--;
            // set map data to explored
            map_data_[row][col] = EXPLORED;
            return true;
        }
    }
    return false;
}

/*
 * Algorithm: Removes the room at (row, col) from the map
 * loop i from 0 to room_count_
 *      if room_position[i] is (row, col)
 *          swap room_position[room_count_-1] with room_position[i]
 *          reset room_position[room_count_-1][0] and room_position[room_count_-1][1] to -1
 *          decrement room_count_
 *          set map data at (row, col) to explored
 *          return true
 * return false
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::removeRoom(int row, int col)
{
    for (int i = 0; i < room_count_; i++)
    {
        if (room_positions_[i][0] == row && room_positions_[i][1] == col)
        {
            // swap i'th room with last room
            room_positions_[i][0] = room_positions_[room_count_ - 1][0];
            room_positions_[i][1] = room_positions_[room_count_ - 1][1];
            // reset last room
            room_positions_[room_count_ - 1][0] = -1;
            room_positions_[room_count_ - 1][1] = -1;
            // decrement room_count_
            room_count_--;
            // set map data to explored
            map_data_[row][col] = EXPLORED;
            return true;
        }
    }
    return false;
}

/*
 * Algorithm: Mark (row, col) as explored, either revealing diamond or empty space
 * if (row, col) is diamond location
 *      mark diamond at player_position_ as found
 * else if (row, col) is a free space
 *      mark space as explored in map data
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
void Map::exploreSpace(int row, int col)
{
    for (int i = 0; i < diamond_count_; i++)
    {
        if (row == diamond_positions_[i][0] && col == diamond_positions_[i][1])
        {
            // mark diamond as found
            diamond_positions_[i][2] = 1;
            return;
        }
    }
    if (isFreeSpace(row, col))
    {
        map_data_[player_position_[0]][player_position_[1]] = EXPLORED;
    }
}

/*
 * Algorithm: Make the player move based on the given command
 * if user inputs w and if its not the top row of the map
 *      Move the player up by one row
 * if user inputs s and if its not the bottom row of the map
 *      Move the player down by one row
 * if user inputs a and if its not the leftmost column
 *      Move the player left by one column
 * if user inputs d and if its not the rightmost column
 *      Move the player right by one column
 * if player moved
 *      if new location is an diamond location
 *          mark new location as explored
 *      return true
 * else
 *      return false
 *
 * Parameters: direction (char)
 * Return: boolean (bool)
 */
bool Map::move(char direction)
{
    // check input char and move accordingly
    switch (toupper(direction))
    {
    case 'W': // if user inputs w, move up if it is an allowed move
        if (player_position_[0] > 0)
        {
            player_position_[0] -= 1;
        }
        else
        {
            return false;
        }
        break;
    case 'S': // if user inputs s, move down if it is an allowed move
        if (player_position_[0] < num_rows_ - 1)
        {
            player_position_[0] += 1;
        }
        else
        {
            return false;
        }
        break;
    case 'A': // if user inputs a, move left if it is an allowed move
        if (player_position_[1] > 0)
        {
            player_position_[1] -= 1;
        }
        else
        {
            return false;
        }
        break;
    case 'D': // if user inputs d, move right if it is an allowed move
        if (player_position_[1] < num_cols_ - 1)
        {
            player_position_[1] += 1;
        }
        else
        {
            return false;
        }
        break;
    default:
        return false;
    }
    // if new location is an diamond location, mark as explored
    if (isDiamondLocation(player_position_[0], player_position_[1]))
    {
        exploreSpace(player_position_[0], player_position_[1]);
    }
    return true;
}

/*
 * Algorithm: This function prints a 2D map in the terminal.
 * Loop i from 0 to number of rows
 *      Loop j from 0 to number of columns
 *          if player position is at (i,j)
 *              print 'F'
 *          else if diamond is at (i,j)
 *              if diamond has been found:
 *                  print '*'
 *              else
 *                  print '-'
 *          else
 *              print the value of (i,j) in map_data_
 *
 * Parameters: none
 * Return: nothing (void)
 */
void Map::displayMap()
{
    for (int i = 0; i < num_rows_; i++)
    {
        for (int j = 0; j < num_cols_; j++)
        {
            if (player_position_[0] == i && player_position_[1] == j)
            {
                cout << FIREBOY;
            }
            else if (map_data_[i][j] == '*')
            { // diamond location, have to check if they were found yet
                for (int k = 0; k < diamond_count_; k++)
                {
                    if (diamond_positions_[k][0] == i && diamond_positions_[k][1] == j)
                    {
                        if (diamond_positions_[k][2] == true)
                        {   
                            cout << DIAMOND;
                        }
                        else
                        {
                            cout << UNEXPLORED;
                        }
                    }
                }
            }
            else
            {
                cout << map_data_[i][j];
            }
        }
        cout << endl;
    }
}

//returns the Temple object that matches the temple stored at a certain row, col
Temple Map:: getTempleNum(int row, int col){
    for(int i = 0; i < room_count_; i++){
        if(room_positions_[i][0] == row && room_positions_[i][1] == col){
            return temples[i];
        }
    }
    return temples[0];
}
//returns a temple at the specified index
Temple Map::getTempleAt(int num){
    return temples[num];
}