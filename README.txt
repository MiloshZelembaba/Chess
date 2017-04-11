2nd Year Final Project
======================
This should be the final verison I think..

To run locally:
~ git clone https://github.com/MiloshZelembaba/Chess.git
~ cd Chess/Pawn\ Pusher
~ xQuartz  (you need to download xQuartz since it uses xWindows)
- make run (ignore the errors)


Instructions:
** this is all controlled from the command line, theres a textual interface printed in the command line
** as well as a graphical interface showing the state of the board
At this point I assume you've made it past "make run"
~ To play a game:
	* Type "game" to start a game and go into the player selection mode
	* Now type one of "human/computer1/.../computer4" for player 1
	* Again type one of the above for player 2
	* type "resign" to resign
	* note all rules are implemented and will be checked (i.e enpassant, castling, valid moves, etc..)
~ How to move:
	* If it's a computer player, just type "move" and it will move
	* For human players, type "move ColumnNumber ColumnNumber" i.e "move a2 a3" moves the white
	  pawn from a2 to a3
~ Setup mode:
	* From the main menu, (right after "make run") type setup and you will be in board setup mode
	* type "+ (PIECE NAME) (COLUMNROW)" to add a piece. i.e "+ Q b3" adds a queen to b3
	* type "- COLUMNROW" to delete a piece at column/row
	* type "done" to finish up, and then "game" to play the game
	* only allowed to leave setup mode when the board is in a valid state
	* NOTE: Soo.. it kinda doesn't work right now for some reason (says stalemate!) but idk why, so 
	  this might not be the newest version of the game since it used to work and I haven't touched anything.
	  Will hopefully be fixed soonish, whenever I feel like getting to it
~ Import/Export:
	* You can import/export game boards but I forget how, I will update when i remember..
	  kinda just made this readme in like 5 min

*********
FYI: computer5 i think is a thing but didn't really work properly
ALSO FYI: computer4 vs. computer4 is pretty fun to watch

Enjoy!!
- Z
*********
