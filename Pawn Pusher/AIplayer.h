#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <string>
#include "board.h"
#include "chessPiece.h"
using namespace std;


// This class is the super class for all computer players
// It belongs to the controller and all methods within the class will be used by controller
class AIplayer {
  protected:
    Board &b; // reference to the game board
    vector<string> allMoves; // vector of all the possible moves it can do
    string colour; // whether its "white" or "black"
    string startSquare(int, int); // used by AIplayer's to convert row,col into file,rank as a string
  public:
    AIplayer(Board&,string); // ctor
    void getMoves(string side); // updates 'allMoves' to obtain the most current version of the moves it can perform
    virtual string bestMove() = 0; // returns the computers best move choice, implemented by all subclasses
};

#endif
