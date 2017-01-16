#ifndef KNIGHT_H
#define KNIGHT_H
#include "chessPiece.h"
#include <string>
using namespace std;

class Knight: public ChessPiece{
    public:
	Knight(string,char,int,int,Board&);
        void updateMoves();
};


#endif
