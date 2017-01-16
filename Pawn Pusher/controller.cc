#include "controller.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sstream>
#include "chessPiece.h"
#include "drawboard.h"
using namespace std;

// the size of the graphical representation of the chess board
const int SIZE = 500;

// ctor
Controller::Controller():b(0), wComp(0), bComp(0), import(false) {}

// This is the central function that controls the game flow
void Controller::play(){
    GFXDisp gfx(SIZE); // the graphical display
    string command; // represents the commands that the user enters
    bool whiteComp = false; // if there is a white computer player
    bool blackComp = false;
    double whiteScore = 0; // the respective overall scores
    double blackScore = 0;
    string turn = "white"; // respresents who's players turn it is
    bool gameRunning = false; // if there is a current game in session
    bool setup = false; // if the user is currently in setupmode
    int movesMade = 0;
    while (cin >> command){ // keeps the program running until Ctrl-D is pressed by the user
	if (command == "game"){ // if the user wants to start a game	   
	    delete wComp;
            delete bComp;
            whiteComp = false;
	    blackComp = false; 
	    string white;
	    string black;
	    cin >> white;
	    cin >> black;
	    if (!setup && !import){b = new Board(); }
	    while(true){
            	if(white == "computer1"){
              	    whiteComp = true;
              	    wComp = new Level1(*b,"white");
             	}
            	if(black == "computer1"){
              	    blackComp = true;
              	    bComp = new Level1(*b,"black");
            	}

	    	if(white == "computer2"){
              	    whiteComp = true;
              	    wComp = new Level2(*b,"white");
            	}
            	if(black == "computer2"){
              	    blackComp = true;
              	    bComp = new Level2(*b,"black");
	    	}
	    	if(white == "computer3"){
              	    whiteComp = true;
              	    wComp = new Level3(*b,"white");
            	}
            	if(black == "computer3"){
              	    blackComp = true;
              	    bComp = new Level3(*b,"black");
	    	}		
                if(white == "computer4"){
                    whiteComp = true;
                    wComp = new Level4(*b,"white");
                }
                if(black == "computer4"){
                    blackComp = true;
                    bComp = new Level4(*b,"black");
	        }
                if(white == "computer5"){
                    whiteComp = true;
                    wComp = new Level5(*b,"white");
                }
                if(black == "computer5"){
                    blackComp = true;
                    bComp = new Level5(*b,"black");
	        }
                
		if (whiteComp && blackComp){ break; } // all players are validly deffined
		if (whiteComp && black != "human"){
		    cout << "invalid black player, please retype it" << endl;
		    cin >> black;
		}else if (blackComp && white != "human"){
		    cout << "invalid white player, please retype it" << endl;
		    cin >> white;
		}else if (!whiteComp && !blackComp){
		    if (white != "human"){
			cout << "invalid white player, please retype it" << endl;
			cin >> white;
		    }if (black != "human"){
			cout << "invalid black player, please retype it" << endl;
			cin >> black;
		    }if (white == "human" && black == "human"){ break; }
		}else{
		    break;
		}
	    }
	    gameRunning = true;
	    
	    setup = false;
	    import = false;
            movesMade = b->getMoves();
 	    gfx.setBoard(b);
   	    gfx.drawBoard(gfx.w1);
	    b->draw();
	    b->updateAllMoves();
	    if (b->getMoves() % 2 == 0){ cout << "White's turn." << endl;}
	    else { cout << "Black's turn." << endl;}
	
	}	
	else if (command == "move" && gameRunning){    	    
		string moveSq;
	   	string moveDest;
                bool isHuman = true;
            	if(whiteComp && b->getMoves() % 2 == 0){
                    isHuman = false;
                    b->updateKingPos();
                    wComp->getMoves("white");
                    b->updateKingPos();
              	    stringstream wMove(wComp->bestMove());
                    b->updateKingPos();
              	    wMove >> moveSq;
              	    wMove >> moveDest;
              	    cout << "White (computer) plays: " << moveSq << " " << moveDest << endl;
            	}else if(blackComp && b->getMoves() % 2 == 1){
              	    isHuman = false;
                    b->updateKingPos();
                    bComp->getMoves("black");
                    b->updateKingPos();
              	    stringstream bMove(bComp->bestMove());
                    b->updateKingPos();
              	    bMove >> moveSq;
              	    bMove >> moveDest;
              	    cout << "Black (computer) plays: " << moveSq << " " << moveDest << endl;
            	}
            	else{
	      	    cin >> moveSq;
	      	    cin >> moveDest;
            	}
            	b->EP_endSq = "";
            	if(b->makeMove(moveSq, moveDest, b->getMoves(), isHuman)){
			gfx.update(gfx.w1,moveSq,moveDest);
  	    	}	
	    	if(movesMade == b->getMoves()) cout << "Invalid move." << endl;
            	else movesMade++;
  
   	    	if(b->getMoves() % 2 == 0) {
              	    if(b->isInCheck("white")) cout << "White is in check!" << endl;// r: " << b->K_row << " c: " << b->K_col << endl;
              	    cout << "White's turn." << endl;
            	}
	    	else {
              	    if(b->isInCheck("black")) cout << "Black is in check!" << endl;// r: " << b->k_row << " c: " << b->k_col << endl;
             	    cout << "Black's turn." << endl;
            	}
 	    
	}
	else if (command == "resign"){
	    gameRunning = false;
	    if (b->getMoves()%2 == 0){ 
		cout << "Black wins!" << endl;
		blackScore += 1; }
	    else { 
		cout << "White wins!" << endl;
		whiteScore += 1; }
  	}
	else if (command == "setup"){
	    if (gameRunning){ cout << "Cannot enter setup mode during gameplay" << endl; }
	    else{
		setup = true;
		cout << "Setup mode" << endl;
		delete b;
		b = new Board();
		gfx.setBoard(b);
		gfx.drawBoard(gfx.w1);
		string modifier;
		b->draw();
		bool whiteKing = true;
		bool blackKing = true;
		while(cin >> modifier){
		    string name,pos,colour;
		    if (modifier == "done"){
			if (!validBoard(*b)){
			    cout << "The board is in an invalid state..." << endl;
			    cout << "Please make the needed modifications before exiting 'setup mode'" << endl;
			}else{ break;}
		    }
		    else if (modifier == "+"){
			cin >> name;
			cin >> pos;
			if (validName(name) && validPos(pos)){
			    b->placePiece(name,pos,modifier);
			}else{ cout << "invalid name or pos" << endl; }
			
		    }else if (modifier == "-"){
		
			cin >> pos;
			if (validPos(pos)){
			    b->placePiece(name,pos,modifier);
			}else{ cout << "invalid pos" << endl; }
		    }else if (modifier == "="){
			cin >> colour;
			if (colour == "white"){ b->setMoves(0); }
			else if (colour == "black"){ b->setMoves(1); }
			else { cout << "Invalid colour" << endl; }
		    }else{
			cout << "Invalid command" << endl;
		    }	    
		b->draw();
		gfx.update(gfx.w1,pos,pos);
		}
	    }
	}   
    else{
	cout << "invalid command" << endl;	
    }

    if (b && b->isGameOver() && gameRunning){
	    gameRunning = false;
	    if (b->inStalemate()){
		whiteScore += 0.5;
		blackScore += 0.5;
	    }	
	    else if (b->getMoves()%2 == 0){
		blackScore++;
	    }else{
	        whiteScore++;
	    }
    }

    }

    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;

    delete wComp;
    delete bComp;
    delete b;
}

void Controller::importGame(string fileName){
    import = true;
    ifstream file(fileName.c_str());
    string line;
    b = new Board();
 
    for (int i=0; i<8; i++){
	file >> line;
  	for (int k=0; k<8; k++){
	    ostringstream row,col,name;
	    char r = 8 - i + '0';
	    char c = k + 'a';
 	    row << r;
	    col << c;
	    name << line[k];
	    if (name.str() == "_"){
		b->placePiece(name.str(),col.str() + row.str(), "-");
	    }else{
		b->placePiece(name.str(),col.str() + row.str(), "+");
	    }
	}
    }
    if(!validBoard(*b)){
	cout << "The saved session is not a valid board state, initial board state being used instead" << endl;
	delete b;
	b = new Board();
 	return;
    }
    file >> line;
    if (line == "W"){ b->setMoves(0); }
    else{ b->setMoves(1); }


}         

bool Controller::validPos(string pos) const{
    if (pos.length() == 2 && 'a' <= pos[0] && pos[0] <= 'h'){
	if ('1' <= pos[1] && pos[1] <= '8'){
	    return true;
	}
    }
    return false;
}

bool Controller::validName(string name) const{
    if (name == "K" || name == "k" || name == "P" || name == "p" || name == "B" || name == "b"
	|| name == "R" || name == "r" || name == "N" || name == "n" || name == "Q" || name == "q") return true;
    return false;
}
 
bool Controller::validBoard(Board &b) const{
    int kCount = 0; // number of black kings
    int KCount = 0; // number of white kings
 
    for (int i=0; i<8; i++){ // checks if there are pawns at the end rows
	if (b.get(0,i) && (b.get(0,i)->getName() == 'p' || b.get(0,i)->getName() == 'P')){
	    return false;
	}if (b.get(7,i) && (b.get(7,i)->getName() == 'p' || b.get(7,i)->getName() == 'P')){
	    return false;
	}
    }
    
    for (int row=0; row<8; row++){
	for (int col=0; col<8; col++){
	    if(b.get(row,col)){
	    	if (b.get(row,col)->getName() == 'k') { kCount++; }
	    	else if (b.get(row,col)->getName() == 'K') { KCount++; }
	    }
	}
    }
    if (kCount != 1 || KCount != 1) { return false; }
    b.updateKingPos();
    if (b.isInCheck("white") || b.isInCheck("black")){ return false;}

    return true;

}
