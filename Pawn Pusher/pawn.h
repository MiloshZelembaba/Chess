#ifndef PAWN_H
#define PAWN_H
#include "chessPiece.h"
#include <string>
using namespace std;

class Pawn: public ChessPiece{
    public:
 	Pawn(string,char,int,int,Board&);
        void updateMoves();
};



#endif
