#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <string>
#include <vector>
#include "board.h"
using namespace std;
//class Board;

class ChessPiece{
    protected:
   	char name;
 	string colour;
    	Board &board;
        int row, col;
        bool onBoard(int, int);
        string rowToRank(int);
        string colToFile(int);
        void attemptAddMove(int, int, int, int);
        void attemptEP(int, int, int, int, string);
        //virtual void updateMoves()=0; // updates 'possibleMoves' to contain all possible moves from current position
    public:
 	const int worth;
        vector<string> possibleMoves;
   	ChessPiece(string,char,int,int,Board &,const int);
        virtual void updateMoves()=0;
        void printMoves();
	// ~ChessPiece();
	char getName() const;
        void set_rc(int, int);
	string getColour() const;
	int getRow() const;
	int getCol() const;
	Board& getBoard() const;
};	



#endif
