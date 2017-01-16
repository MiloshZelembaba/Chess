#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>
class ChessPiece;
class TextDisplay;
using namespace std;

class Board{
    ChessPiece *board[8][8];
    int nMoves;
    TextDisplay *td;
    bool noMoves(string);
    bool stalemate;
    void checkAndDoPawnPromotion(ChessPiece**, int);
    void checkPromoAI(ChessPiece**, int);
    public:
   	string startSquare(int,int);
    	bool isThreatend(ChessPiece*);
  	bool resultInCheck(string);
	vector<ChessPiece*> whiteChessMen;
    	vector<ChessPiece*> blackChessMen;
  	void printVectors();
	bool inStalemate() const;
        int k_row, k_col, K_row, K_col;
        int EP_row, EP_col;
        string EP_endSq;
	Board();
	~Board();
	void setMoves(int);
	void placePiece(string,string,string);
	void draw() const;
	void updateBoard(ChessPiece *,int,int,int,int); // a ChessPiece will call this to update the board
        void EP_updateBoard(ChessPiece *,int,int,int,int,string);
        void updateAllMoves();
  	void removeChessMen(ChessPiece*);
    	void addChessMan(ChessPiece*);
 	bool isGameOver();
	bool makeMove(string, string, int, bool);
	int getMoves() const;
        void updateKingPos();
        void setKingPos(bool, int, int);
	bool onBoard(int, int);
        void set(int, int, ChessPiece *);
        bool isInCheck(string);
   	ChessPiece *get(int,int) const;

};

#endif
	
