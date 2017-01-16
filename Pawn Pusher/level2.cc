#include "level2.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

Level2::Level2(Board &b,string colour): AIplayer(b,colour) {}

string Level2::bestMove(){
    srand(time(NULL));
    int numMoves = allMoves.size();
    vector<string> checkMoves;
    vector<string> captureMoves; 

    if (numMoves > 0){
	for (unsigned i=0; i < numMoves; i++){
	    int row = 8 - allMoves.at(i)[4] + '0';
	    int col = allMoves.at(i)[3] - 'a';

	    if (b.resultInCheck(allMoves.at(i))){ // adds moves that result in a check
		checkMoves.push_back(allMoves.at(i));
	    }

	    // adds caputring moves
	    else if (b.get(row,col)){ // don't need to check if the chesspiece is the opposite colour, since it wouldn't be a legal move if it was the same colour
		captureMoves.push_back(allMoves.at(i));
	    }
  	}
    }else{
	return "well this should never happen right?";
    }
    
    if (!checkMoves.empty()){
	int moveIndex = rand() % checkMoves.size();
	return checkMoves.at(moveIndex);
    }else if(!captureMoves.empty()){
	int moveIndex = rand() % captureMoves.size();
	return captureMoves.at(moveIndex);
    }else{
	int moveIndex = rand() % numMoves;
	return allMoves.at(moveIndex);
    }
}	
    
