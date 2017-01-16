#include "window.h"
#include <string>
class Board;
using namespace std;

class GFXDisp {
  Board *b;
  char board[8][8];
  int size;
  int Xoffset;
  int Yoffset;
  public:
   Xwindow w1;
   GFXDisp(int);
   void setBoard(Board*);
   void update(Xwindow &,string,string);
   void drawBoard(Xwindow &);
}; 
