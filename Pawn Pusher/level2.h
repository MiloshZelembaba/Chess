#ifndef LEVEL2_H
#define LEVEL2_H

#include "AIplayer.h"
#include <string>
using namespace std;

class Level2: public AIplayer{
    public:
	Level2(Board&,string);
	string bestMove();
};

#endif
