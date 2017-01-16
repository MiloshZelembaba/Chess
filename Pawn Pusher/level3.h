#ifndef LEVEL3_H
#define LEVEL3_H
#include "AIplayer.h"
#include <string>
using namespace std;

class Level3: public AIplayer{
    public:
	Level3(Board&,string);
	string bestMove();
};

#endif
