#ifndef KING_H
#define KING_H
#include "chessPiece.h"
#include <string>
using namespace std;

class King: public ChessPiece{
    bool moved;
    public:
  	bool setMoved();
	King(string,char,int,int,Board&);
        void updateMoves();
};


#endif
