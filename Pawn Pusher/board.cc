#include "board.h"
#include "chessPiece.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <iostream>
#include <string>
#include "textDisplay.h"
using namespace std;

Board::Board(): k_col(4), k_row(0), K_col(4), K_row(7), EP_row(-1), EP_col(-1), EP_endSq(""),
 nMoves(0), td(new TextDisplay), stalemate(false){ 
// initialies the board to the default start game configuration
 
    // initializing all the black pieces
    board[0][0] = new Rook("black",'r',0,0,*this);
    board[0][1] = new Knight("black",'n',0,1,*this);
    board[0][2] = new Bishop("black",'b',0,2,*this);
    board[0][3] = new Queen("black",'q',0,3,*this);
    board[0][4] = new King("black",'k',0,4,*this);
    board[0][5] = new Bishop("black",'b',0,5,*this); 
    board[0][6] = new Knight("black",'n',0,6,*this);
    board[0][7] = new Rook("black",'r',0,7,*this);
    for (int i=0; i<8; i++){
	board[1][i] = new Pawn("black",'p',1,i,*this);
    }

    // initializing all the white pieces
    board[7][0] = new Rook("white",'R',7,0,*this);
    board[7][1] = new Knight("white",'N',7,1,*this);
    board[7][2] = new Bishop("white",'B',7,2,*this);
    board[7][3] = new Queen("white",'Q',7,3,*this);
    board[7][4] = new King("white",'K',7,4,*this);
    board[7][5] = new Bishop("white",'B',7,5,*this); 
    board[7][6] = new Knight("white",'N',7,6,*this);
    board[7][7] = new Rook("white",'R',7,7,*this);
    for (int i=0; i<8; i++){
	board[6][i] = new Pawn("white",'P',6,i,*this);
    }
 
    for (int i=2; i<6; i++){
	for (int j=0; j<8; j++){
	    board[i][j] = 0; // all empty spaces are set to NULL
  	}
    }
}

Board::~Board(){
    for (int i=0; i<8; i++){
	for (int j=0; j<8; j++){
	    delete board[i][j];
	}
    }
    delete td;
}

void Board::draw() const{
    td->notify(board);
}

void Board::addChessMan(ChessPiece *piece){
//    cout << piece->getColour();
    if (piece->getColour() == "white"){
	whiteChessMen.push_back(piece);
    }else{
	blackChessMen.push_back(piece);
    }
}

// removes chessmen from their respective lits if they have been eliminated
// theres no direct remove function for vectors so i have to do it this way :(

void Board::removeChessMen(ChessPiece* tmp){
    for (vector<ChessPiece*>::iterator it = whiteChessMen.begin(); it != whiteChessMen.end(); it++){
   	if ((*it) == tmp){ 
	    whiteChessMen.erase(it);
	    break;
	}
    }
    for (vector<ChessPiece*>::iterator it = blackChessMen.begin(); it != blackChessMen.end(); it++){
   	if ((*it) == tmp){ 
	    blackChessMen.erase(it); 
	    break;
	}
    }
}

bool Board::noMoves(string colour){
    for (int row=0; row<8; row++){
	for (int col=0; col<8; col++){
	    ChessPiece *piece = get(row,col);
	    if (piece && piece->getColour() == colour && !(piece->possibleMoves.empty())){ 
		return false; 
	    }
    	}
    }
    return true;
}

void Board::printVectors(){
    for (vector<ChessPiece*>::iterator it=whiteChessMen.begin(); it != whiteChessMen.end(); it++){
        cout << (*it)->getName() << ",";
    }
}


bool Board::inStalemate() const{
    return stalemate;
}

bool Board::isGameOver(){
    updateKingPos();
    bool no_moves;
    bool check;
    if (nMoves%2 == 0){
     	check = isInCheck("white");
	no_moves = noMoves("white");
   	if (check && no_moves){
	    cout << "Checkmate!" << endl;
	    cout << "Black Wins!" << endl;
	    return true;
     	}else if (!check && no_moves){
	    stalemate = true;
	    cout << "Stalemate!" << endl;
	    return true;
   	}else{ return false; }

    }else{
	check = isInCheck("black");
	no_moves = noMoves("black");
   	if (check && no_moves){
	    cout << "Checkmate!" << endl;
	    cout << "White Wins!" << endl;
	    return true;
     	}else if (!check && no_moves){
	    stalemate = true;
	    cout << "Stalemate!" << endl;
	    return true;
   	}else{ return false; }
    }
}	

// returns the private field nMoves
int Board::getMoves() const{ return nMoves;}

string Board::startSquare(int row,int col){
    string s = "..";
    s[0] = col + 'a';
    s[1] = 8 - row + '0';
    return s;
}


bool Board::isThreatend(ChessPiece* cp){
    string colour = cp->getColour();
    for (int row=0; row<8; row++){
	for (int col=0; col<8; col++){
	    if (get(row,col) && get(row,col)->getColour() != colour){
		vector<string> vec = get(row,col)->possibleMoves;
		string pos = startSquare(cp->getRow(),cp->getCol());
		for (int i=0; i<vec.size(); i++){
		    if (vec.at(i) == pos){ return true; }
	  	}
	    }
	}
    }
    return false;
}

void Board::updateAllMoves(){
    updateKingPos();
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
	    if(this->get(i, j)){
                this->get(i, j)->updateMoves();
                //this->get(i, j)->printMoves();
            }
        }
    }
    //cout << endl;
}

void Board::checkPromoAI(ChessPiece **cpp, int row){
    ChessPiece *tmp;
    ChessPiece *piece = *cpp;
    bool isWhitePawn = piece->getName() == 'P';
    bool isBlackPawn = piece->getName() == 'p';
    if(isWhitePawn && row == 1){
      tmp = new Queen("white", 'Q', piece->getRow(), piece->getCol(), piece->getBoard());
      delete (*cpp);
      *cpp = tmp;
    }
    else if(isBlackPawn && row == 6){
      tmp = new Queen("black", 'q', piece->getRow(), piece->getCol(), piece->getBoard());
      delete (*cpp);
      *cpp = tmp;
    }
}

void Board::checkAndDoPawnPromotion(ChessPiece **cpp,int row){
    ChessPiece *tmp;
    ChessPiece *piece = *cpp;
    string newPiece;
    if ((piece->getName() == 'p' && piece->getRow() == 6) || (piece->getName() == 'P' && piece->getRow() == 1)){
	if (row == 1 && piece->getName() == 'P'){
	    while(cin >> newPiece){
 	    	if (newPiece == "Q"){
		    tmp = new Queen("white",newPiece[0],piece->getRow(), piece->getCol(),piece->getBoard());
		    break;
		}else if (newPiece == "B"){
		    tmp = new Bishop("white",newPiece[0],piece->getRow(), piece->getCol(),piece->getBoard());
		    break;	
 		}else if (newPiece == "N"){
		    tmp = new Knight("white",newPiece[0],piece->getRow(), piece->getCol(),piece->getBoard());
		    break;
		}else if (newPiece == "R"){
		    tmp = new Rook("white",newPiece[0],piece->getRow(), piece->getCol(),piece->getBoard());
		    break;
		}else { cout << "invalid piece" << endl; }
	    }
	}else if (row == 6 && piece->getName() == 'p'){
	    while(cin >> newPiece){
 	    	if (newPiece == "q"){
		    tmp = new Queen("black",newPiece[0],piece->getRow(), piece->getCol(),piece->getBoard());
		    break;
		}else if (newPiece == "b"){
		    tmp = new Bishop("black",newPiece[0],piece->getRow(), piece->getCol(),piece->getBoard());
		    break;	
 		}else if (newPiece == "n"){
		    tmp = new Knight("black",newPiece[0],piece->getRow(), piece->getCol(),piece->getBoard());
		    break;
		}else if (newPiece == "r"){
		    tmp = new Rook("black",newPiece[0],piece->getRow(), piece->getCol(),piece->getBoard());
		    break;
		}else { cout << "invalid piece" << endl; }
	    }
 	}
    delete (*cpp);
    *cpp = tmp;
    }
}
	

	
bool Board::makeMove(string moveSq, string moveDest, int nMoves, bool isHuman){
    //removeChessMen();
    string turn = "white";
    if(nMoves % 2 == 1) turn = "black";
    if(moveSq.length() == 2 && moveSq[0] >= 'a' && moveSq[0] <= 'h' && moveSq[1] >= '1' && moveSq[1] <= '8'){
        int s_col = moveSq[0] - 'a';
        int s_row = 8 - moveSq[1] + '0';
        ChessPiece *cp = get(s_row, s_col);
        if(cp && cp->getColour() == turn){
            vector<string> vec = cp->possibleMoves;
            for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
                if(moveDest == *it){
		/// CASTLING STUFF
		    char name = board[s_row][s_col]->getName();
		    if (name == 'k' || name == 'K' || name == 'R' || name == 'r'){
			Rook* tmpR = dynamic_cast<Rook*>(board[s_row][s_col]);
			King* tmpK = dynamic_cast<King*>(board[s_row][s_col]);
			if (tmpK){
			    tmpK->setMoved();
			}else if (tmpR){
			    tmpR->setMoved();
			}
		    }
		    if (name == 'K' && moveSq == "e1"){
			if (moveDest == "c1"){
			    updateBoard(board[7][0],7,0,7,3); // moves the rook
			}else if (moveDest == "g1"){
			    updateBoard(board[7][7],7,7,7,5);
		    	}
		    }else if (name == 'k' && moveSq == "e8"){
			if (moveDest == "c8"){
			    updateBoard(board[0][0],0,0,0,3);
			}else if (moveDest == "g8"){
			    updateBoard(board[0][7],0,7,0,5);
			}
		    }	
		// CASTLING STUFF
                    int f_col = moveDest[0] - 'a';
                    int f_row = 8 - moveDest[1] + '0';
                    bool wPawnEP = name == 'P' && f_row - s_row == -2;
                    bool bPawnEP = name == 'p' && f_row - s_row == 2;
                    int EP_activeSq_row = 5;
                    if(cp->getColour() == "black") EP_activeSq_row = 3;
                    if(wPawnEP || bPawnEP){ EP_row = EP_activeSq_row; EP_col = f_col; }
                    else{ EP_row = -1; EP_col = -1; }
                    if(isHuman) checkAndDoPawnPromotion(&cp, s_row);
                    else checkPromoAI(&cp, s_row);
                    if((name == 'P' || name == 'p') && moveDest == EP_endSq){
                      EP_updateBoard(cp, s_row, s_col, f_row, f_col, cp->getColour());
                    } 
                    else updateBoard(cp, s_row, s_col, f_row, f_col);
                    draw();
                    updateAllMoves();
                    setMoves(nMoves + 1);
                    return true;
                }
            }
        }
    }
    return false;
}

//  This funcion is ment to be called by a ChessPiece to notify the board of the new position
//  of the ChessPiece
void Board::updateBoard(ChessPiece *piece, int s_row,int s_col, int f_row, int f_col){
    //removeChessMen(board[f_row][f_col]);
    delete board[f_row][f_col];
    board[f_row][f_col] = piece; // updates the position of the piece on the board
    board[f_row][f_col]->set_rc(f_row, f_col);
    if(piece->getName() == 'K'){ K_row = f_row; K_col = f_col; }
    if(piece->getName() == 'k'){ k_row = f_row; k_row = f_col; }
    board[s_row][s_col] = 0; // remove piece from where it used to be
}

void Board::EP_updateBoard(ChessPiece *piece, int s_row, int s_col, int f_row, int f_col, string side){
    int backward = 1;
    if(side == "black") backward = -1;
    //removeChessMen(board[f_row + backward][f_col]);
    delete board[f_row + backward][f_col];
    board[f_row][f_col] = piece;
    board[f_row][f_col]->set_rc(f_row, f_col);
    board[s_row][s_col] = 0;
}

void Board::set(int row, int col, ChessPiece *piece){
   if (piece && piece->getName() == 'K'){
	K_col = col;
	K_row = row;
   }else if (piece && piece->getName() == 'k'){
	k_col = col;
	k_row = row;
   }
   board[row][col] = piece;
   if(piece){ piece->set_rc(row,col);}
}    

ChessPiece* Board::get(int row, int col) const{
    return board[row][col];
}

void Board::setMoves(int n){ nMoves = n; }

bool Board::onBoard(int row, int col){
    if(row < 0 || row > 7 || col < 0 || col > 7) return false;
    return true;
}
// string must be of the form: "a2 a3"
bool Board::resultInCheck(string pos){
    int f_row = 8 - pos[4] + '0';
    int f_col = pos[3] - 'a';
    int s_row = 8 - pos[1] + '0';
    int s_col = pos[0] - 'a';
    string colour = "white";
    if(get(s_row,s_col)->getColour() == "white"){ colour = "black";}

    ChessPiece *tmp = get(f_row,f_col);

    set(f_row,f_col,get(s_row,s_col));
    set(s_row,s_col,0);
    if (isInCheck(colour)){
	set(s_row,s_col,get(f_row,f_col));
	set(f_row,f_col,tmp);
  	return true;
    }else{
	set(s_row,s_col,get(f_row,f_col));
 	set(f_row,f_col,tmp);
	return false;
    }
}

bool Board::isInCheck(string side){
    int king_row, king_col;
    int new_row, new_col;
    updateKingPos();
    king_row = K_row;
    king_col = K_col;
    char enemies[6] = {'p' ,'r' ,'n' ,'b' , 'k', 'q'};
    if(side == "black"){
        updateKingPos();
        king_row = k_row;
        king_col = k_col;
        for(int i = 0; i < 6; i++){
            enemies[i] = enemies[i] - 'a' + 'A';
        }
    }
    int dir1[] = {0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1, -1, 0, -1, 1};
    int dir2[] = {1, 2, 1, -2, -1, 2, -1, -2, 2, 1, 2, -1, -2, 1, -2, -1};
    for (int i = 0; i < 8; i++){
        for(int j = 1 ;; j++){
            int new_row = king_row + j * dir1[2 * i];
            int new_col = king_col + j * dir1[2 * i + 1];
            if(!onBoard(new_row, new_col)) break;
            if(i % 2 == 0){ //going out horizontally//vertically
                if(this->get(new_row, new_col)){
                    if(j == 1){//one square orthonally from king
                        if(this->get(new_row, new_col)->getName() == enemies[4]){
                            //cout << "Check via king." << endl;
                            return true;
                        }
                    }                    
                    if(this->get(new_row, new_col)->getName() == enemies[1] ||
                       this->get(new_row, new_col)->getName() == enemies[5]){
                       //cout << "Check via rook/queen." << endl;
                       return true;
                    }
                    else break;
                }
            }else{ //going out diagonally
                if(this->get(new_row, new_col)){
                    if(j == 1){ //one square diagonally from king
                        bool aheadKing = false;
                        if(side == "white" && new_row < king_row) aheadKing = true;
                        else if(side == "black" && new_row > king_row) aheadKing = true;         
               
                        if(this->get(new_row, new_col)->getName() == enemies[4] ||
                           (this->get(new_row, new_col)->getName() == enemies[0] && aheadKing)){
                            //cout << "Check via king/pawn." << endl;
                            return true;
                        }
                    }
                    if(this->get(new_row, new_col)->getName() == enemies[3] ||
                       this->get(new_row, new_col)->getName() == enemies[5]){
                        //cout << "Check via bishop/queen." << endl;
                        return true;
                    }
                    else break;
                }
            }    
        }
    }
	    for (int i = 0; i < 8; i++){
        int new_row = king_row + dir2[2 * i];
        int new_col = king_col + dir2[2 * i + 1];
        if(onBoard(new_row, new_col) && this->get(new_row, new_col) &&
           this->get(new_row, new_col)->getName() == enemies[2]){
            //cout << "Check via knight." << endl;
            return true;
        }

    }
    return false;                                
}    
            
void Board::updateKingPos(){
    for (int row=0; row<8; row++){
	for (int col=0; col<8; col++){
	    if (board[row][col] && board[row][col]->getName() == 'k'){
		k_col = col;
		k_row = row;
	    }else if (board[row][col] && board[row][col]->getName() == 'K'){
		K_col = col;
		K_row = row;
	    }
 	}
    }
} 

void Board::setKingPos(bool isWhite, int row, int col){
  if(isWhite){ K_row = row; K_col = col; }
  else k_row = row; k_col = col;
}          

void Board::placePiece(string name, string pos, string action){
    if (action == "+"){ 
  	 if ('a' <= name[0]){ // black piece
	    int row = 8 - pos[1] + '0'; 
	    int col = pos[0] - 'a';
	    string colour = "black";
    	    // some sort of method here to remove the piece from the players 'pieces' list
	    delete board[row][col];
	    if (name == "r") { board[row][col] = new Rook(colour,name[0],row,col,*this); }
	    else if (name == "b") { board[row][col] = new Bishop(colour,name[0],row,col,*this); }
	    else if (name == "p") { board[row][col] = new Pawn(colour,name[0],row,col,*this); }
	    else if (name == "q") { board[row][col] = new Queen(colour,name[0],row,col,*this); }
	    else if (name == "k") { board[row][col] = new King(colour,name[0],row,col,*this); }
	    else if (name == "n") { board[row][col] = new Knight(colour,name[0],row,col,*this); }
	    else { cout << "how did this happen?" << endl; }
    	}else{ // white piece	
	    int row = 8 - pos[1] + '0'; 
	    int col = pos[0] - 'a';
	    string colour = "white";
    	    // some sort of method here to remove the piece from the players 'pieces' list
	    delete board[row][col];
	    if (name == "R") { board[row][col] = new Rook(colour,name[0],row,col,*this); }
	    else if (name == "B") { board[row][col] = new Bishop(colour,name[0],row,col,*this); }
	    else if (name == "P") { board[row][col] = new Pawn(colour,name[0],row,col,*this); }
	    else if (name == "Q") { board[row][col] = new Queen(colour,name[0],row,col,*this); }
	    else if (name == "K") { board[row][col] = new King(colour,name[0],row,col,*this); }
	    else if (name == "N") { board[row][col] = new Knight(colour,name[0],row,col,*this); }
	    else { cout << "how did this happen?" << endl; }
        }
    }else{
	int row = 8 - pos[1] + '0';
	int col = pos[0] - 'a';
	removeChessMen(board[row][col]);
	delete board[row][col];
	board[row][col] = 0;
    }
}
    

