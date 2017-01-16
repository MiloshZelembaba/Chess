#include "level3.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>


Level3::Level3(Board &b, string colour): AIplayer(b,colour) {}

string Level3::bestMove(){
    srand(time(NULL));
    int numMoves = allMoves.size();
    vector<string> checkMoves;
    vector<string> captureMoves; 
    vector<string> avoidCapture;

    for (int row=0; row<8; row++){
	for (int col=0; col<8; col++){
	    if (b.get(row,col) && b.get(row,col)->getColour() == colour){
		if (b.isThreatend(b.get(row,col))){
		    vector<string> vec = b.get(row,col)->possibleMoves;
		
		    for (unsigned i=0; i<vec.size(); i++){
			string moveStart = startSquare(row,col);
			string moveDest = vec.at(i);
			avoidCapture.push_back(moveStart + " " + moveDest);
		    }
		}
	    }
	}
    }	

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
    
    if(!avoidCapture.empty()){
    	int moveIndex = rand() % avoidCapture.size();
	return avoidCapture.at(moveIndex);
    }else if (!checkMoves.empty()){
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
 
