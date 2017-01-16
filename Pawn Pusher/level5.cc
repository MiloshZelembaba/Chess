#include "level5.h"
#include "queen.h"
#include <vector>
#include <map>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

Level5::Level5(Board &b, string colour): AIplayer(b,colour) {}

int Level5::scoreFor(string mySide){
  string yourSide = "black";
  if(mySide == "black") yourSide = "white";
  int score = 0;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(b.get(i, j)){
        if(b.get(i, j)->getColour() == mySide) score += b.get(i, j)->worth;
        else score -= b.get(i, j)->worth;
      }
    }
  }
  return score;
}
      
string Level5::bestMove(){
  moveMap.clear();
  generateMinima(1, true);
  string chosenMove;
  vector<string> tiedMoves;
  int max = -1000;
  for(multimap<int,string>::iterator it = moveMap.begin(); it != moveMap.end(); ++it){
    if(it->first > max){
      max = it->first;
      tiedMoves.clear();
      tiedMoves.push_back(it->second);
    }
    else if(it->first == max){
      tiedMoves.push_back(it->second);
    }
  }
  srand(time(NULL));
  int numMoves = tiedMoves.size();
  if(numMoves > 0){
    int moveIndex = rand() % numMoves;
    chosenMove = tiedMoves.at(moveIndex);
  } 
  return chosenMove;  
}

void Level5::generateMinima(int depth, bool firstEval){
  vector<string> oppMoves;
  bool whiteKS, whiteQS, blackKS, blackQS, enPass, promo;
  string mySide = "white"; string yourSide = "black";
  char myQueenChar = 'Q'; char yourQueenChar = 'q';
  if(colour == "black"){
    mySide = "black"; yourSide = "white";
    myQueenChar = 'q'; char yourQueenChar = 'Q';
  }
  for(int i = 0; i < 8; i++){ for(int j = 0; j < 8; j++){ if(b.get(i,j)) b.get(i,j)->updateMoves(); }}
  getMoves(mySide);
  for(vector<string>::iterator it1 = allMoves.begin(); it1 != allMoves.end(); ++it1){
    string thinkMove = *it1;
    if(firstEval) firstMove = thinkMove;
    whiteKS = false; whiteQS = false; blackKS = false; blackQS = false; enPass = false, promo = false;
    int s_row = 8 - thinkMove[1] + '0';
    int s_col = thinkMove[0] - 'a';
    int f_row = 8 - thinkMove[4] + '0';
    int f_col = thinkMove[3] - 'a';
    ChessPiece *piece = b.get(s_row, s_col);
    ChessPiece *taken = 0;
    ChessPiece *rook = 0;
    ChessPiece *pawn = 0;
    ChessPiece* queen = new Queen(mySide, myQueenChar, f_row, f_col, b);
    if(piece->getName() == 'K'){
      if(s_col - f_col == -2) whiteKS = true;
      else if(s_col - f_col == 2) whiteQS = true;
    }else if(piece->getName() == 'k'){
      if(s_col - f_col == -2) blackKS = true;
      else if(s_col - f_col == 2) blackQS = true;
    }
    else if(piece->getName() == 'P' || piece->getName() == 'p'){
      if(s_col != f_col && !b.get(f_row, f_col)) enPass = true;
      else if(f_row == 0 || f_row == 7) promo = true;
    }
    if(whiteKS){
      rook = b.get(7,7);
      b.set(7,4,0);
      b.set(7,6,piece);
      b.set(7,7,0);
      b.set(7,5,rook);
    }else if(whiteQS){
      rook = b.get(7,0);
      b.set(7,4,0);
      b.set(7,2,piece);
      b.set(7,0,0);
      b.set(7,3,rook);
    }else if(blackKS){
      rook = b.get(0,7);
      b.set(0,4,0);
      b.set(0,6,piece);
      b.set(0,7,0);
      b.set(0,5,rook);
    }else if(blackQS){
      rook = b.get(0,0);
      b.set(0,4,0);
      b.set(0,2,piece);
      b.set(0,0,0);
      b.set(0,3,rook);
    }else if(enPass){
      int backward = 1;
      if(mySide == "black") backward = -1;
      pawn = b.get(f_row + backward, f_col);
      b.set(s_row, s_col, 0);
      b.set(f_row, f_col, piece);
      b.set(f_row + backward, f_col, 0);
    }else if(promo){
      if(b.get(f_row, f_col)) taken = b.get(f_row, f_col);
      pawn = b.get(s_row, s_col);
      b.set(s_row, s_col, 0);
      b.set(f_row, f_col, queen);
    }else{
      if(b.get(f_row, f_col)) taken = b.get(f_row, f_col);
      b.set(s_row, s_col, 0);
      b.set(f_row, f_col, piece);
    }
    b.updateKingPos();
    oppMoves.clear();
    for(int k = 0; k < 8; k++){
      for(int l = 0; l < 8; l++){
        if(b.get(k,l) && b.get(k,l)->getColour() == yourSide){
          b.get(k,l)->updateMoves();
          vector<string> vec = b.get(k,l)->possibleMoves;
          for(vector<string>::iterator it2 = vec.begin(); it2 != vec.end(); ++it2){
            string st = startSquare(k,l);
            string fn = *it2;
            oppMoves.push_back(st + " " + fn);
          }
        }
      }
    }
    if(firstEval) min = 1000;
    string minMove;
    bool whiteKS2, whiteQS2, blackKS2, blackQS2, enPass2, promo2;    
    for(vector<string>::iterator it3 = oppMoves.begin(); it3 != oppMoves.end(); ++it3){
      string thinkMoveResp = *it3;
      whiteKS2 = false; whiteQS2 = false; blackKS2 = false; blackQS2 = false; enPass2 = false, promo2 = false;
      int s_row2 = 8 - thinkMoveResp[1] + '0';
      int s_col2 = thinkMoveResp[0] - 'a';
      int f_row2 = 8 - thinkMoveResp[4] + '0';
      int f_col2 = thinkMoveResp[3] - 'a';
      ChessPiece *piece2 = b.get(s_row2, s_col2);
      ChessPiece *taken2 = 0;
      ChessPiece *rook2 = 0;
      ChessPiece *pawn2 = 0;
      ChessPiece *queen2 = new Queen(yourSide, yourQueenChar, f_row2, f_col2, b);
  
      if(piece2->getName() == 'K'){
        if(s_col2 - f_col2 == -2) whiteKS2 = true;
        else if(s_col2 - f_col2 == 2) whiteQS2 = true;
      }else if(piece2->getName() == 'k'){
        if(s_col2 - f_col2 == -2) blackKS2 = true;
        else if(s_col2 - f_col2 == 2) blackQS2 = true;
      }
      else if(piece2->getName() == 'P' || piece2->getName() == 'p'){
        if(s_col2 != f_col2 && !b.get(f_row2, f_col2)) enPass2 = true;
        else if(f_row2 == 0 || f_row2 == 7) promo2 = true;
      }

      if(whiteKS2){
        rook2 = b.get(7,7);
        b.set(7,4,0);
        b.set(7,6,piece2);
        b.set(7,7,0);
        b.set(7,5,rook2);
      }else if(whiteQS2){
        rook2 = b.get(7,0);
        b.set(7,4,0);
        b.set(7,2,piece2);
        b.set(7,0,0);
        b.set(7,3,rook2);
      }else if(blackKS2){
        rook2 = b.get(0,7);
        b.set(0,4,0);
        b.set(0,6,piece2);
        b.set(0,7,0);
        b.set(0,5,rook2);
      }else if(blackQS2){
        rook2 = b.get(0,0);
        b.set(0,4,0);
        b.set(0,2,piece2);
        b.set(0,0,0);
        b.set(0,3,rook2);
      }else if(enPass2){
        int backward2 = -1;
        if(yourSide == "white") backward2 = 1;
        pawn2 = b.get(f_row2 + backward2, f_col2);
        b.set(s_row2, s_col2, 0);
        b.set(f_row2, f_col2, piece2);
        b.set(f_row2 + backward2, f_col2, 0);
      }else if(promo2){
        if(b.get(f_row2, f_col2)) taken2 = b.get(f_row2, f_col2);
        pawn2 = b.get(s_row2, s_col2);
        b.set(s_row2, s_col2, 0);
        b.set(f_row2, f_col2, queen2);
      }else{
        if(b.get(f_row2, f_col2)) taken2 = b.get(f_row2, f_col2);
        b.set(s_row2, s_col2, 0);
        b.set(f_row2, f_col2, piece2);
      }
      
      if(depth == 1){
        if(scoreFor(mySide) < min){
          min = scoreFor(mySide);
          minMove = firstMove;
        }
      }
      else generateMinima(depth - 1, false);
      
      if(whiteKS2){
        b.set(7,4,piece2);
        b.set(7,6,0);
        b.set(7,7,rook2);
        b.set(7,5,0);
      }else if(whiteQS2){
        b.set(7,4,piece2);
        b.set(7,2,0);
        b.set(7,0,rook2);
        b.set(7,3,0);
      }else if(blackKS2){
        b.set(0,4,piece2);
        b.set(0,6,0);
        b.set(0,7,rook2);
        b.set(0,5,0);
      }else if(blackQS2){
        b.set(0,4,piece2);
        b.set(0,2,0);
        b.set(0,0,rook2);
        b.set(0,3,0);
      }else if(enPass2){
        int backward2 = -1;
        if(yourSide == "white") backward2 = 1;
        b.set(s_row2, s_col2, piece2);
        b.set(f_row2, f_col2, 0);
        b.set(f_row2 + backward2, f_col2, pawn2);
      }else if(promo2){
        b.set(s_row2, s_col2, pawn2);
        if(taken2){
          b.set(f_row2, f_col2, taken2);
        }else b.set(f_row2, f_col2, 0);
      }else{
        b.set(s_row2, s_col2, piece2);
        if(taken2){
          b.set(f_row2, f_col2, taken2);
        }else b.set(f_row2, f_col2, 0);
      }
      delete queen2;
    }
   
    if(whiteKS){
      b.set(7,4,piece);
      b.set(7,6,0);
      b.set(7,7,rook);
      b.set(7,5,0);
    }else if(whiteQS){
      b.set(7,4,piece);
      b.set(7,2,0);
      b.set(7,0,rook);
      b.set(7,3,0);
    }else if(blackKS){
      b.set(0,4,piece);
      b.set(0,6,0);
      b.set(0,7,rook);
      b.set(0,5,0);
    }else if(blackQS){
      b.set(0,4,piece);
      b.set(0,2,0);
      b.set(0,0,rook);
      b.set(0,3,0);
    }else if(enPass){
      int backward = 1;
      if(mySide == "black") backward = -1;
      b.set(s_row, s_col, piece);
      b.set(f_row, f_col, 0);
      b.set(f_row + backward, f_col, pawn);
    }else if(promo){
      b.set(s_row, s_col, pawn);
      if(taken){
        b.set(f_row, f_col, taken);
      }else b.set(f_row, f_col, 0);
    }else{
      b.set(s_row, s_col, piece);
      if(taken){
        b.set(f_row, f_col, taken);
      }else b.set(f_row, f_col, 0);
    }
    b.updateKingPos();
    if(firstEval) moveMap.insert(pair<int,string>(min, firstMove));
    delete queen;  
  }    
}      
