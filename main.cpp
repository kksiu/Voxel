#include <GL/glew.h>

#include <SDL.h>

#include "Game.h"

int main(int argc, char *args[])
{
    //set the context of the window
    Game game(800, 600, "Hello");
    
    game.run();
    
    return EXIT_SUCCESS;
}
