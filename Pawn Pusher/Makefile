# super simple makefile
# call it using 'make NAME=name_of_code_file_without_extension'
# (assumes a .cpp extension)
NAME = chess

#
# Add $(MAC_OPT) to the compile line for Mac OSX.
MAC_OPT = "-I/opt/X11/include"

all:
	@echo "Compiling..."
	g++ -o $(NAME) main.cc AIplayer.cc bishop.cc board.cc chessPiece.cc controller.cc king.cc knight.cc level1.cc pawn.cc queen.cc rook.cc textDisplay.cc level2.cc level3.cc level4.cc level5.cc drawboard.cc window.cc -L/usr/X11R6/lib -lX11 -lstdc++ $(MAC_OPT)

run: all
	@echo "Running..."
	./$(NAME)

clean:
	-rm animation clipping doublebuffer drawing drawing.min
	-rm eventloop eventloop.min hello.min null null.min openwindow openwindow.min
