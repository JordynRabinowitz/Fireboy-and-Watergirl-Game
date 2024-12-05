// gameDriver.cpp
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#include <iostream>
#include "Temple.h"
#include "Fireboy.h"
#include "Watergirl.h"
#include "ExtraLivesBoard.h"
#include "Map.h"
#include <cassert>

using namespace std;

int main(){

    Temple newnew = Temple();
    Temple newt = Temple(); 

    Fireboy fb = Fireboy(); 
    //check that fb is initialized properly and getters work
    assert(fb.getLives() == 0);
    assert(fb.getCharacter() == 'F');
    assert(fb.getDiamonds().size() == 0);
    assert(fb.getNumDoorsReached() == 0);
    assert(fb.getImmunity() == false);
    //check that fb setters work
    fb.setLives(1);
    fb.addDiamonds(1);
    fb.addNumDoorsReached();
    fb.setImmunity(true);
    assert(fb.getLives() == 1);
    assert(fb.getDiamonds().size() == 1);
    assert(fb.sumPoints() == 6); //if array properly added to then sum calculated correctly
    assert(fb.getNumDoorsReached() == 1);
    assert(fb.getImmunity() == true);

    Watergirl wg = Watergirl();
    //check that wg is initialized properly
    assert(wg.getLives() == 0);
    assert(wg.getCharacter() == 'W');
    assert(wg.getDiamonds().size() == 0);
    assert(wg.getNumDoorsReached() == 0);
    assert(wg.getImmunity() == false);
    //check that wg setters work
    wg.setLives(1);
    wg.addDiamonds(1);
    wg.addNumDoorsReached();
    wg.setImmunity(true);
    assert(wg.getLives() == 1);
    assert(wg.getDiamonds().size() == 1);
    assert(wg.sumPoints() == 6); //if array properly added to then sum calculated correctly
    assert(wg.getNumDoorsReached() == 1);
    assert(wg.getImmunity() == true);
    // checks getTempleDataAt()
    assert(newnew.getTempleDataAt(0,0) == '/'); 
    //check random temples created
    newt.printTemple(fb.getFireBoyRow(), fb.getFireBoyCol(), wg.getWatergirlRow(), wg.getWatergirlCol()); 
    newnew.printTemple(fb.getFireBoyRow(), fb.getFireBoyCol(), wg.getWatergirlRow(), wg.getWatergirlCol()); 
    //checks getLives(), getPostion(), getRow/Col(), and setPosition() works correctly 
    newnew.movePlayers(fb, wg);
    newnew.movePlayers(fb, wg);
    //check that players are moved (means above getters/setters work)
    newnew.printTemple(fb.getFireBoyRow(), fb.getFireBoyCol(), wg.getWatergirlRow(), wg.getWatergirlCol()); 

    ExtraLivesBoard board1 = ExtraLivesBoard();
    //test getters
    assert(board1.getPlayerRow() == 0);
    assert(board1.getPlayerCol() == 0);
    assert(board1.getBoardData(3,3) == '-');
    
    //tests print board works correctly
    board1.printBoard();
    //tests setPlayerPosition and setExplored()
    board1.movePlayer();  
    board1.movePlayer();
    board1.movePlayer();
    board1.movePlayer();
    board1.movePlayer();
    board1.printBoard();

    //test setters
    board1.setFireLives(fb);
    board1.setWaterLives(wg);
    cout << "Fire lives: " << fb.getLives() << endl;
    cout << "Water lives: " << wg.getLives() << endl;

    //test add room works on map, adds a temple
    Map new_map = Map();
    new_map.displayMap();
    new_map.move('D');
    new_map.move('D');
    bool room_added = new_map.addRoom();
    new_map.displayMap();
    if(room_added){
        cout << "Room added!" << endl;
    }
    else{
        cout <<"failed" << endl;
    }


    return 0;
}