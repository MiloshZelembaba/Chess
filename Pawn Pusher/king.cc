#include "king.h"
#include <string>
#include  "board.h"
#include "rook.h"
using namespace std;


King::King(string colour, char name, int row, int col, Board &board):moved(0), ChessPiece(colour,name,row,col,board,0){
    board.addChessMan(this);
}

bool King::setMoved(){
    moved = true;
}

void King::updateMoves(){
  this->possibleMoves.clear();
  int s_row = this->row;
  int s_col = this->col;
  string side = this->colour;
  int dir[] = {0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1, -1, 0, -1, 1};
  for(int i = 0; i < 8; i++){
    int new_row = s_row + dir[2 * i];
    int new_col = s_col + dir[2 * i + 1];
    	
    if(onBoard(new_row, new_col)){
      if(!board.get(new_row, new_col)){
        attemptAddMove(s_row, s_col, new_row, new_col);
      }else if(board.get(new_row, new_col)->getColour() != side){
        attemptAddMove(s_row, s_col, new_row, new_col); 
      }
    }
  }
  if (side == "white" && !moved && s_row == 7 && s_col == 4){
	ChessPiece* piece = board.get(7,0);
	Rook* tmp = dynamic_cast<Rook*>(piece);
	if (tmp && tmp->getName() == 'R' && !tmp->getMoved()){
	    if (!board.get(7,1) && !board.get(7,2) && !board.get(7,3)){
		board.set(7,3,this);
                board.K_col = 3;
		board.set(7,4,0);
		if (!board.isInCheck("white")){
		    board.set(7,2,this);
                    board.K_col = 2;
                    board.set(7,3,0);
		    if (!board.isInCheck("white")){
			board.set(7,4,this);
                        board.K_col = 4;
			board.set(7,2,0);
			attemptAddMove(7,4,7,2);
		    }
		}
		board.set(7,4,this);
                board.K_col = 4;
		board.set(7,3,0);
		board.set(7,2,0);
	    }
	}
	piece = board.get(7,7);
	tmp = dynamic_cast<Rook*>(piece);
	if (tmp && tmp->getName() == 'R' && !tmp->getMoved()){
	    if (!board.get(7,5) && !board.get(7,6)){
		board.set(7,5,this);
                board.K_col = 5;
		board.set(7,4,0);
		if (!board.isInCheck("white")){
		    board.set(7,6,this);
                    board.K_col = 6;
		    board.set(7,5,0);
		    if (!board.isInCheck("white")){
			board.set(7,4,this);
                        board.K_col = 4;
			board.set(7,6,0);
			attemptAddMove(7,4,7,6);
		    }
		}
		board.set(7,4,this);
                board.K_col = 4;
		board.set(7,5,0);
		board.set(7,6,0);
	    }
	}
    }else if (side == "black" && !moved && s_row == 0 && s_col == 4){
	ChessPiece* piece = board.get(0,0);
	Rook* tmp = dynamic_cast<Rook*>(piece);
	if (tmp && tmp->getName() == 'r' && !tmp->getMoved()){
	    if (!board.get(0,1) && !board.get(0,2) && !board.get(0,3)){
		board.set(0,3,this);
                board.k_col = 3;
		board.set(0,4,0);
		if (!board.isInCheck("black")){
		    board.set(0,2,this);
                    board.k_col = 2;
		    board.set(0,3,0);
		    if (!board.isInCheck("black")){
			board.set(0,4,this);
                        board.k_col = 4;
			board.set(0,2,0);
			attemptAddMove(0,4,0,2);
		    }
		}
		board.set(0,4,this);
                board.k_col = 4;
		board.set(0,3,0);
		board.set(0,2,0);
	    }
	}
	piece = board.get(0,7);
	tmp = dynamic_cast<Rook*>(piece);
	if (tmp && tmp->getName() == 'r' && !tmp->getMoved()){
	    if (!board.get(0,5) && !board.get(0,6)){
		board.set(0,5,this);
                board.k_col = 5;
		board.set(0,4,0);
		if (!board.isInCheck("black")){
		    board.set(0,6,this);
                    board.k_col = 6;
		    board.set(0,5,0);
		    if (!board.isInCheck("black")){
			board.set(0,4,this);
                        board.k_col = 4;
			board.set(0,6,0);
			attemptAddMove(0,4,0,6);
		    }
		}
		board.set(0,4,this);
                board.k_col = 4;
		board.set(0,5,0);
		board.set(0,6,0);
	    }
	}
    }
}


