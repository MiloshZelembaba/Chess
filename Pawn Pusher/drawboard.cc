#include "drawboard.h"
#include "board.h"
#include <sstream>
#include "chessPiece.h"

GFXDisp::GFXDisp(int n): b(0), size(n), Xoffset(-size/40), Yoffset(size/40),  w1(Xwindow(size,size)){};

void GFXDisp::setBoard(Board* b){
    this->b = b;
}

void GFXDisp::update(Xwindow &disp,string start,string finish){
    int txtCol = Xwindow::Black;
    int squareSize = size/10;
    int sqCol = Xwindow::Wheat;
    int s_col = start[0] - 'a';
    int s_row = 8 - start[1] + '0';
    int f_col = finish[0] - 'a';
    int f_row = 8 - finish[1] + '0';

    if (0 <= f_row && f_row <=7 && 0<=f_col && f_col <= 7){    
    	if ((s_row + s_col)%2 == 1){ sqCol = Xwindow::DarkGoldenrod; }
    	disp.fillRectangle(squareSize * (s_col+1), squareSize * (s_row+1),squareSize,squareSize,sqCol);
	sqCol = Xwindow::Wheat;
	if ((f_row + f_col)%2 == 1){ sqCol = Xwindow::DarkGoldenrod; }
    	disp.fillRectangle(squareSize * (f_col+1), squareSize * (f_row+1),squareSize,squareSize,sqCol);
    	if (b->get(f_row,f_col)){
	    stringstream ss;
            ss << b->get(f_row,f_col)->getName();
   	    disp.drawBigString(squareSize * (f_col + 1.5) + Xoffset, (f_row+1.5)*squareSize + Yoffset ,ss.str(),txtCol);      
    	}
    }
}
void GFXDisp::drawBoard(Xwindow &disp){
  int squareSize = size/10;
  int sqCol = Xwindow::Wheat;
  int txtCol = Xwindow::Black;
  for(int i = 1; i < 9; i++){
    for(int j = 1; j < 9; j++){  
      disp.fillRectangle(squareSize * j, squareSize * i, squareSize, squareSize, sqCol);
      if(sqCol == Xwindow::Wheat && j != 8) sqCol = Xwindow::DarkGoldenrod;
      else if(j != 8) sqCol = Xwindow::Wheat;
    }
  }
  for(int i = 1; i < 9; i++){
    char cRank = 8 - i + '0' + 1;
    char cFile = 'A' + i - 1;
    std::string sRank;
    std::string sFile;
    std::stringstream ssRank;
    std::stringstream ssFile;
    ssRank << cRank;
    ssFile << cFile;
    ssRank >> sRank;
    ssFile >> sFile;
    disp.drawBigString(squareSize/3, squareSize * i + squareSize/1.5, sRank, txtCol);
    disp.drawBigString(squareSize * i + squareSize/3, squareSize/1.5, sFile, txtCol);
    disp.drawBigString(28 * squareSize/3, squareSize * i + squareSize/1.5, sRank, txtCol);
    disp.drawBigString(squareSize * i + squareSize/3, 14.5 * squareSize/1.5, sFile, txtCol);
  }

  for (int row=0; row<8; row++){
      for (int col=0; col<8; col++){
          if(b->get(row,col)){
	      stringstream ss;
	      ss << b->get(row,col)->getName();
	      disp.drawBigString(squareSize * (col+1.5) + Xoffset, (row+1.5)*(squareSize) + Yoffset, ss.str(), txtCol);
	  }
      }
  }

 }  

