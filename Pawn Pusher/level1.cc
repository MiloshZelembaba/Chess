#include "level1.h"
#include <stdlib.h>
#include <time.h>

Level1::Level1(Board &b,string colour): AIplayer(b,colour) {}

string Level1::bestMove(){
  srand(time(NULL));
  int numMoves = allMoves.size();
  if(numMoves > 0){
    int moveIndex = rand() % numMoves;
    return allMoves.at(moveIndex);
  }
  return "I have no moves. I'm a sad AI.";
}
