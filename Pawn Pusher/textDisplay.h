#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
//#include "view.h"
#include "board.h"

class TextDisplay{
    void print(ChessPiece* const [8][8]) const;

    public:
	 void notify(ChessPiece* const [8][8]) const;
};

#endif
