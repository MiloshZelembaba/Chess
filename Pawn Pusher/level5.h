#ifndef LEVEL5_H
#define LEVEL5_H
#include "AIplayer.h"
#include <string>
#include <map>
using namespace std;

class Level5: public AIplayer{
    private:
        int scoreFor(string);
        int min;
        string firstMove;
        multimap<int,string> moveMap;
        void generateMinima(int, bool);       
    public:
	Level5(Board&,string);
	string bestMove();
};

#endif
