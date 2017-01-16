#include "AIplayer.h"
#include <iostream>
#include <string>

// Two parameter ctor takes in the current game board and the colour that the computer player is
AIplayer::AIplayer(Board &b,string colour): b(b), colour(colour){}


// converts row,col into a string of file,rank.
// Requires: row and col both be valid (between 0 and 7 inclusve)
string AIplayer::startSquare(int row, int col){
  string s = "..";
  s[0] = col + 'a';
  s[1] = 8 - row + '0';
  return s;
}

// It will update 'allMoves' to obtain the most up-to-date vector of all it's possible moves
// Requires: side must be either "white" or "black", updates moves for the corresponding side
void AIplayer::getMoves(string side){
  allMoves.clear(); // must clear old list since all previous moves aren't necessarily still valid
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(b.get(i,j) && b.get(i,j)->getColour() == side){ // finding a ChessPiece that has colour 'side'
        vector<string> vec = b.get(i,j)->possibleMoves; // obtain all of that piece's possible moves
        for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
          string moveStart = startSquare(i,j);
          string moveDest = *it;
          allMoves.push_back(moveStart + " " + moveDest); // add the piece's possible moves to 'allMoves'
        }
      }
    }
  }
}         
         
