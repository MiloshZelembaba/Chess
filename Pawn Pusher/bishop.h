#ifndef BISHOP_H
#define BISHOP_H
#include "chessPiece.h"
#include <string>
using namespace std;

class Bishop: public ChessPiece{
    public:
	Bishop(string,char,int,int,Board&);
        void updateMoves();
};


#endif
