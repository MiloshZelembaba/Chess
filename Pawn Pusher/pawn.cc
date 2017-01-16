#include "pawn.h"
#include <string>
#include "board.h"
using namespace std;

Pawn::Pawn(string colour, char name, int row, int col, Board &board): ChessPiece(colour,name,row,col,board,1){
    board.addChessMan(this);
}

void Pawn::updateMoves(){
  this->possibleMoves.clear();
  int s_row = this->row;
  int s_col = this->col;
  string side = this->colour;
  int forward = -1; int first_rank = 6; int EP_atk_row = 3;
  char oppPawn = 'p';
  if(side == "black"){ forward = 1; first_rank = 1; EP_atk_row = 4; oppPawn = 'P'; }
  int dir[] = {-1 , 1};
  if(!board.get(s_row + forward, s_col)){
    attemptAddMove(s_row, s_col, s_row + forward, s_col);
    if(s_row == first_rank && !board.get(s_row + 2 * forward, s_col)){
      attemptAddMove(s_row, s_col, s_row + 2 * forward, s_col);
    }
  }
  for(int i = 0; i < 2; i++){
    int new_col = s_col + dir[i];
    int new_row = s_row + forward;
    if(onBoard(new_row, new_col) && board.get(new_row, new_col) && board.get(new_row, new_col)->getColour() != side){
      attemptAddMove(s_row, s_col, new_row, new_col);
    }
  }
  if(s_row == EP_atk_row){
    for(int i = 0; i < 2; i++){
      int new_col = s_col + dir[i];
      int new_row = s_row + forward;
      if(s_row == board.EP_row && new_col == board.EP_col){
        attemptEP(s_row, s_col, new_row, new_col, side);
      }
    }
  }    
}
