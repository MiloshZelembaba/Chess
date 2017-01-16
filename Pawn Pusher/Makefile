all: pp9k

pp9k: main.o AIplayer.o bishop.o board.o chessPiece.o controller.o king.o knight.o level1.o pawn.o queen.o rook.o textDisplay.o level2.o level3.o level4.o level5.o drawboard.o window.o
	g++ main.o AIplayer.o bishop.o board.o chessPiece.o controller.o king.o knight.o level1.o pawn.o queen.o rook.o textDisplay.o level2.o level3.o level4.o level5.o drawboard.o window.o -o pp9k -lX11

main.o: main.cc
	g++ -c main.cc

AIplayer.o: AIplayer.cc
	g++ -c AIplayer.cc

bishop.o: bishop.cc
	g++ -c bishop.cc

board.o: board.cc
	g++ -c board.cc

chessPiece.o: chessPiece.cc
	g++ -c chessPiece.cc

controller.o: controller.cc
	g++ -c controller.cc

king.o: king.cc
	g++ -c king.cc

knight.o: knight.cc
	g++ -c knight.cc

level1.o: level1.cc
	g++ -c level1.cc

pawn.o: pawn.cc
	g++ -c pawn.cc

queen.o: queen.cc
	g++ -c queen.cc

rook.o: rook.cc
	g++ -c rook.cc

textDisplay.o: textDisplay.cc
	g++ -c textDisplay.cc

level2.o: level2.cc
	g++ -c level2.cc

level3.o: level3.cc
	g++ -c level3.cc

level4.o: level4.cc
	g++ -c level4.cc

level5.o: level5.cc
	g++ -c level5.cc

drawboard.o: drawboard.cc
	g++ -c drawboard.cc

window.o: window.cc
	g++ -c window.cc

clean:
	rm -f *o pp9k

