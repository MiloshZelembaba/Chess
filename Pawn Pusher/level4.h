#ifndef LEVEL4_H
#define LEVEL4_H
#include "AIplayer.h"
#include <string>
using namespace std;

class Level4: public AIplayer{
    private:
        int scoreFor(string);
    public:
	Level4(Board&,string);
	string bestMove();
};

#endif
