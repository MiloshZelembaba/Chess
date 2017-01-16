#include "rook.h"
#include <string>
#include "board.h"
using namespace std;

Rook::Rook(string colour, char name, int row, int col, Board &board): moved(0),ChessPiece(colour,name,row,col,board,5){
    board.addChessMan(this);
}

bool Rook::getMoved() const{
    return moved;
}

void Rook::setMoved(){
    moved = true;
}

void Rook::updateMoves(){
  this->possibleMoves.clear();
  int s_row = this->row;
  int s_col = this->col;
  string side = this->colour;
  int dir[] = {1, 0, -1, 0, 0, 1, 0, -1};
  for(int i = 0; i < 4; i++){
    for(int j = 1;; j++){
      int new_row = s_row + j * dir[2 * i];
      int new_col = s_col + j * dir[2 * i + 1];
      if(!onBoard(new_row, new_col)) break; 
      if(!board.get(new_row, new_col)) attemptAddMove(s_row, s_col, new_row, new_col);
      else if(board.get(new_row, new_col)->getColour() != side){
        attemptAddMove(s_row, s_col, new_row, new_col);
        break;
      }
      else break;
    }
  }
}
