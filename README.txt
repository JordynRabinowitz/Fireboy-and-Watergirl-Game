------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ -std=c++17 g++ Fireboy.cpp Watergirl.cpp Temple.cpp ExtraLivesBoard.cpp Map.cpp 
playGame.cpp -o proj3
Run: ./proj3
------------------------
DEPENDENCIES
------------------------
Fireboy.h, Watergirl.h, Temple.h, ExtraLivesBoard.h, and Map.h must be in the same directory as the cpp 
files in order to compile. ExtraLivesBoard.cpp and Temple.cpp must include Watergirl.h and Fireboy.h to compile. 
Map.cpp must inlude Temple.h to compile. Include all five ".h" files (listed above) in the directory of playGame.cpp.
------------------------
SUBMISSION INFORMATION
------------------------
CSCI 1300 Fall 2022 Project 2
Author: Jordyn Rabinowitz
Recitation: 306 - Zach Atkins
Date: Nov 28, 2022
------------------------
ABOUT THIS PROJECT
------------------------
This game is modeled after Watergirl and Fireboy on coolmathgames.com. The rules are almost identitical, so if you are 
familiar with that game you will enjoy this one! The goal is to reach 1000 points by exploring temples and finding diamonds.
You lose when fireboy and watergirl have zero lives left. Have fun playing!
