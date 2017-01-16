#ifndef LEVEL1_H
#define LEVEL1_H

#include "AIplayer.h"
#include <string>
using namespace std;

class Level1 : public AIplayer {
  public:
    Level1(Board&,string);
    string bestMove();  
};

#endif
