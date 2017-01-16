#include "chessPiece.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
	
ChessPiece::ChessPiece(string colour,char name, int row, int col, Board &board, int worth):
				colour(colour), name(name), row(row), col(col), board(board), worth(worth){
    //updateMoves();
}

Board& ChessPiece::getBoard() const{
    return board;
}

int ChessPiece::getCol() const{
    return col;
}

int ChessPiece::getRow() const{
    return row;
}

bool ChessPiece::onBoard(int row, int col){
  if(row < 0 || row > 7 || col < 0 || col > 7) return false;
  return true;
}

string ChessPiece::rowToRank(int row){
  string s = ".";
  s[0] = 8 - row + '0';
  return s;
}

string ChessPiece::colToFile(int col){
  string s = ".";
  s[0] = col + 'a';
  return s;
}

char ChessPiece::getName() const{
    return name;
}

string ChessPiece::getColour() const{
    return colour;
}

void ChessPiece::set_rc(int _r, int _c){
    this->row = _r;
    this->col = _c;
}

void ChessPiece::printMoves(){
    for(vector<string>::iterator it = this->possibleMoves.begin(); it != this->possibleMoves.end(); ++it){
        cout << this->getColour() << " " << this->getName() << " " << *it << endl;
    }
}

void ChessPiece::attemptAddMove(int s_row, int s_col, int f_row, int f_col){
    ChessPiece *start = board.get(s_row, s_col);
    string side = start->getColour();
    bool isKing = start->name == 'K' || start->name == 'k';
    ChessPiece *finish = board.get(f_row, f_col);
    board.set(f_row, f_col, start);
    board.set(s_row, s_col, 0);
    if(isKing) board.setKingPos(side == "white", f_row, f_col);
    if(!board.isInCheck(side)){
      this->possibleMoves.push_back(colToFile(f_col) + rowToRank(f_row));
    }
    if(isKing) board.setKingPos(side == "white", s_row, s_col);
    board.set(f_row, f_col, finish);
    board.set(s_row, s_col, start);
}

void ChessPiece::attemptEP(int s_row, int s_col, int f_row, int f_col, string side){
    int backward = 1;
    if(side == "black") backward = -1;
    ChessPiece *start = board.get(s_row, s_col);
    ChessPiece *finish = board.get(f_row, f_col + backward);
    board.set(f_row + backward, f_col, 0);
    board.set(f_row, f_col, start);
    board.set(s_row, s_col, 0);
    if(!board.isInCheck(side)){
      board.EP_endSq = colToFile(f_col) + rowToRank(f_row);
      this->possibleMoves.push_back(colToFile(f_col) + rowToRank(f_row));
    }
    board.set(f_row + backward, f_col, finish);
    board.set(f_row, f_col, 0);
    board.set(s_row, s_col, start);
}
        
