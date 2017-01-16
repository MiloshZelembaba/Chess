#ifndef QUEEN_H
#define QUEEN_H
#include "chessPiece.h"
#include <string>
using namespace std;

class Queen: public ChessPiece{
    public:
	Queen(string,char,int,int,Board&);
        void updateMoves();
};


#endif
