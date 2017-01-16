#include "board.h"
#include "AIplayer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include <string>
using namespace std;

// This class contains all the methods to coordinate gameflow
class Controller{
    Board *b; // pointer to the current game board
    AIplayer *wComp; // white computer player
    AIplayer *bComp; // black computer player
    bool import; // represents if a board state has been imported or not
    bool validName(string) const; // used in "setup mode" to justify a valid piece name
    bool validPos(string) const; // used in "setup mode" to justify a valid piece position
    bool validBoard(Board&) const; // used to justify if a given board state is valid to start a game with
    public:
	Controller(); // ctor
	void play(); // controls the game flow
	void importGame(string); // imports a game state
};
