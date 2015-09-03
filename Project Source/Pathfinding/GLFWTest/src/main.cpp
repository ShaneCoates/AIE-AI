#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <MathLib.h>
#include "Framework.h"
#include <iostream>
#include "Texture2D.h"
#include <time.h>
#include <stdlib.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

#include "Game.h"

int main( int argc, char* argv[] )
{	

	srand((unsigned int)time(NULL));


	bool fullscreen = false;
	for(int i=0; i<argc; i++)
	{
		std::cout << argv[i] << std::endl;
		if(strcmp(argv[i], "fullscreen") == 0)
			fullscreen = true;
	}

	Game *theGame = new Game(WINDOW_WIDTH, WINDOW_HEIGHT, "Pathfinding Exercise", fullscreen);
	theGame->RunGame();
	delete theGame;
	
	return 0;

}