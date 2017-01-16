#include "controller.h"
#include <iostream>

int main(int argc, char *argv[]){
    Controller c;
    if (argc == 2){
	std::cout << "Importing game state" << std::endl;
	c.importGame(argv[1]);
    }
    c.play();
}
