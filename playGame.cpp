// playGame.cpp
// CSCI 1300 Fall 2022
// Author: Jordyn Rabinowitz
// Recitation: 306 – Zach Atkins
#include <iostream>
#include "Temple.h"
#include "Fireboy.h"
#include "Watergirl.h"
#include "ExtraLivesBoard.h"
#include "Map.h"
#include <fstream>

using namespace std;

/* ends game
prints the scoreboard along with if the player lost or won
*/
void Endgame(Fireboy& fb, Watergirl& wg){
    string file_info;
    ifstream fin2;
    fin2.open("scores.txt");
    if(fin2.is_open()){
        string line;
        while(getline(fin2, line)){
            file_info += ("\n" + line);
        }
        fin2.close();
    }
    if(!(wg.getLives() == 0 && fb.getLives() == 0) && (fb.sumPoints() + wg.sumPoints()) >= 1000){
        ofstream fout("scores.txt");
        fout << file_info + " - Won"; 
        fout.close();
        cout << "You have reached 1000 points! Congrats you have won!" << endl;
        cout << "Fireboy lives remaining: " << fb.getLives() << endl;
        cout << "Watergirl lives remaining: " << wg.getLives() << endl; 
    }
    else if(wg.getLives() == 0 && fb.getLives() == 0){
        ofstream fout("scores.txt");
        fout << file_info + " - Lost"; 
        fout.close();
        cout << "Fireboy and Watergirl are dead. Sorry you lost :(" << endl;
    }
    else{
        ofstream fout("scores.txt");
        fout << file_info + " - Lost"; 
        fout.close();
        cout << "Quit game before reaching 1000 points. Sorry you lost :(" << endl;
    }
    ifstream fin3;
        fin3.open("scores.txt");
        if(fin3.is_open()){
            string line;
            while(getline(fin3, line)){
                cout << line << endl;
            }
            fin3.close();
        }
    return; 
}

// as long as fireboy and watergirl have not both reached their doors or died, the game is printed and the player is prompted to move
void playTemple(Temple& temp, Fireboy& fb, Watergirl& wg){
    while(!(temp.isFireExit(fb) && temp.isWaterExit(wg)) && !(wg.getLives() == 0 && fb.getLives() == 0)){

        //CHECK THIS EVERY MOVE!!!! game end condition
        int total_points = fb.sumPoints() + wg.sumPoints();
        if(total_points >= 1000){
            Endgame(fb, wg);
        }

        temp.printTemple(fb.getFireBoyRow(), fb.getFireBoyCol(), wg.getWatergirlRow(), wg.getWatergirlCol());
        temp.movePlayers(fb, wg);
    }
    if(wg.getLives() == 0 && fb.getLives() == 0){
        Endgame(fb, wg);
    }
    else if(temp.isFireExit(fb) && temp.isWaterExit(wg)){
        cout << "Exited temple." << endl;
        cout << "Fireboy lives: " << fb.getLives() << endl;
        cout << "Watergirl lives: " << wg.getLives() << endl;
        
        
        int total_points = fb.sumPoints() + wg.sumPoints();
        cout << "Total points: " << total_points << endl;

        fb.setFireBoyPosition(0,1);
        wg.setWatergirlPosition(0,2);
    }
}

//compile to play: g++ -std=c++17 Fireboy.cpp Watergirl.cpp Temple.cpp ExtraLivesBoard.cpp Map.cpp playGame.cpp -o proj3

int main(){

    srand(time(0));

    string username;
    bool not_unique = true;
    cout << "Introduction:\n\nWelcome to Fireboy and Watergirl the game! Your goal is to reach 1000 points by finding hidden\ndiamonds in the temples and going through temple doors.\n\nPoint system:\n\nDiamonds on map = 6 points\nDiamonds in temples = 5 Points\nTemple doors = 5 points\n\nMap Rules:\n\nExplore the map to find hidden diamonds and enter temple’s represented by “T” !\n\nTemple Rules:\n\nMove the players throughout the temple. Reach both doors to exit. \nFireboy CANNOT walk through water (“~”), -1 life if he does. Watergirl CANNOT walk\nthrough fire  (“^”), -1 life if she does. But, if one of the players steps on a button the other \ngains immunity to water/fire respectively.\n\nGame start:\n\nFireboy and Watergirl have zero lives right now. You will start by finding hidden lives. Explore \nthe board to gain lives! Go to the door to exit the board. \n\nEnter a username to start: " << endl;
    cin >> username;
    string file_info;
    while(not_unique){
        ifstream fin;
        fin.open("scores.txt");
        if(fin.is_open()){
            string user;
            while(fin >> user){
                if(user == username){
                    cout << "Username already exists. Please enter a new one: " << endl;
                    cin >> username;
                }
                else{
                    not_unique = false;
                }
            }

            fin.close();
        }
        else{
            not_unique = false;
        }
    }
    ifstream fin2;
    fin2.open("scores.txt");
    if(fin2.is_open()){
        string user;
        while(getline(fin2, user)){
            file_info += ("\n" + user);
        }
        fin2.close();
    }
    ofstream fout("scores.txt");
    fout << file_info << endl;
    fout << username; 
    fout.close();

    //players
    Watergirl wg;
    Fireboy fb;

    //start game with gaining lives
    ExtraLivesBoard board1;
    cout <<"Player: W = up, S = down, D = right, A = left" << endl;
    board1.printBoard();
    board1.movePlayer();
    while(!board1.isExit()){
        board1.printBoard();
        board1.movePlayer();
    }
    board1.setFireLives(fb);
    board1.setWaterLives(wg);
    cout << "Fireboy's lives: " << fb.getLives() << endl;
    cout << "Watergirl's lives: " << wg.getLives() << endl;

    //add rooms to the map
    Map map1 = Map();
    int num_temples = 0;
    while(num_temples < 5){
        bool added = map1.addRoom();
        if(added){
            num_temples++;
        }
    }
    //add diamonds to the map
    // About 70% max of map covered in diamonds
    int random_diamonds = (rand() % 100) + 1;
    int count_diamonds = 0;
    while(count_diamonds < random_diamonds){
        bool added = map1.addDiamond();
        if(added){
            count_diamonds++;
        }
    } 
     
    int choice = -1;
    //start game loop
    while(choice == -1){
      cout << "\n------ Menu ------\n1. Explore map\n2. Earn lives\n3. Create your own temple\n4. Play random temple\n5. View number of lives and points\n6. Scoreboard\n7. Quit\n" << endl;  
      cin >> choice;
      //explore map
      if(choice == 1){
        char move;
        cout <<"Player: W = up, S = down, D = right, A = left" << endl;
        map1.displayMap(); 
        cin >> move;
        map1.move(move);
        while(!map1.isDungeonExit(map1.getPlayerRow(), map1.getPlayerCol())){
            map1.displayMap(); 
            cin >> move;
            map1.move(move);
            if(map1.isDiamondLocation(map1.getNumRows(), map1.getNumCols())){
                fb.addDiamonds(3);
                wg.addDiamonds(3);
            }
            else if(map1.isRoomLocation(map1.getPlayerRow(), map1.getPlayerCol())){
                map1.displayMap(); 
                Temple play = map1.getTempleNum(map1.getPlayerRow(), map1.getPlayerCol());
                int play_q;
                cout << "1. Enter temple\n2. Do not enter. Enter a move" << endl;
                cin >> play_q;
                if(play_q == 1){
                    Temple temp = map1.getTempleNum(map1.getPlayerRow(), map1.getPlayerCol());
                    //play function
                    playTemple(temp, fb, wg);
                }
                else if(play_q == 2){
                    cin >> move;
                    map1.move(move);
                }
            }
        } 
        
        choice = -1;
      }
      // earn lives
      else if(choice == 2){
        ExtraLivesBoard board2 = ExtraLivesBoard();
        cout <<"Player: W = up, S = down, D = right, A = left" << endl;
        board2.printBoard();
        board2.movePlayer();
        while(!board2.isExit()){
            board2.printBoard();
            board2.movePlayer();
        }
        board2.setFireLives(fb);
        board2.setWaterLives(wg);
        cout << "Fireboy's lives: " << fb.getLives() << endl;
        cout << "Watergirl's lives: " << wg.getLives() << endl;

        choice = -1;
      }
      //create your own temple
      else if(choice == 3){
        Temple customize = Temple();
        cout << "\nChoose what you want to customize and then enter a position. Rows are 0-9. Columns are 0-19.\n" << endl;
        int option = -1;
        while(option == -1){
            customize.printTemple(fb.getFireBoyRow(), fb.getFireBoyCol(), wg.getWatergirlRow(), wg.getWatergirlCol());
            cout << "\n------ Customize Options ------\n1. Set water\n2. Set fire\n3. Set walkway\n4. Set button\n5. play!\n" << endl;
            cin >> option;
            int row;
            int col;
            if(option != 5 && (option == 1 || option == 2 || option == 3 || option == 4)){
                cout << "Enter a row: " << endl;
                cin >> row;
                cout << "Enter a column: " << endl;
                cin >> col;
            }
            if(option == 1){
                customize.setWater(row, col);
                option = -1;
            }
            else if(option == 2){
                customize.setFire(row, col);
                option = -1;
            }
            else if(option == 3){
                customize.setWalkway(row, col);
                option = -1;
            }
            else if(option == 4){
                customize.setButton(row, col);
                option = -1;
            }
            else if (option == 5){
                fb.setFireBoyPosition(0,1);
                wg.setWatergirlPosition(0,2);
                playTemple(customize, fb, wg);
            }
            else{
                cout << "Invalid option. Please choose again." << endl;
                option = -1;
            }
        }
        
        choice = -1;
      }
      //play random temple
      else if(choice == 4){
        int random = (rand() % 5) + 1;
        random--;
        Temple random_temple = map1.getTempleAt(random);
        playTemple(random_temple, fb, wg);

        choice = -1;
      }
      //display number of lives and points
      else if(choice == 5){
        cout << username << ":" << endl;
        cout << "Fireboy lives: " << fb.getLives() << endl;
        cout << "Watergirl lives: " << wg.getLives() << endl;
        int total_points = fb.sumPoints() + wg.sumPoints();
        cout << "Total points: " << total_points << endl;

        choice = -1;
      }
      //print scoreboard
      else if(choice == 6){
        ifstream fin3;
        fin3.open("scores.txt");
        if(fin3.is_open()){
            string line;
            while(getline(fin3, line)){
                cout << line << endl;
            }
            fin3.close();
        }

        choice = -1;
      }
      //quit
      else if(choice == 7){
        Endgame(fb, wg);
        return 0;
      }
      //not valid choice entered
      else{
        cout << "Invalid option. Please choose again." << endl;
        choice = -1;
      }
    }
    return 0;
}