#include "textDisplay.h"
#include <iostream>
#include "chessPiece.h"
using namespace std;


void TextDisplay::notify(ChessPiece* const board[8][8]) const{
    print(board);
}

void TextDisplay::print(ChessPiece* const board[8][8]) const{
    for (int row=0; row<8; row++){
	cout << 8 - row << " ";
	for (int col=0; col<8; col++){
 	    if (!board[row][col]){
		if ((row+col)%2 == 0){
		    cout << "_";
		}else{
		    cout << " ";
		}
	    }else{
		cout << board[row][col]->getName();
	    }
  	}
	cout << endl;
    }
    cout << "  abcdefgh" << endl << endl;
}
