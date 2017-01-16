#include "knight.h"
#include <string>
#include "board.h"
using namespace std;

Knight::Knight(string colour,char name, int row, int col, Board &board): ChessPiece(colour,name,row,col,board,3){
    board.addChessMan(this);
}

void Knight::updateMoves(){
  this->possibleMoves.clear();
  int s_row = this->row;
  int s_col = this->col;
  string side = this->colour;
  int dir[] = {1, 2, 1, -2, -1, 2, -1, -2, 2, 1, 2, -1, -2, 1, -2, -1};
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
}
