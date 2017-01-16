#ifndef ROOK_H
#define ROOK_H
#include "chessPiece.h"
#include <string>
#include <vector>
using namespace std;

class Rook: public ChessPiece{
    bool moved;
    public:
	bool getMoved() const;
	void setMoved();
	Rook(string,char,int,int,Board&);
        void updateMoves();
};

#endif
