#include <string>

#include <GL/glew.h>
#include <SDL.h>

#include "Game.h"

int main(int argc, char *args[])
{
    
    unsigned int width = 800;
    unsigned int height = 600;
    std::string title = "Hello";
    
    //set the context of the window
    Game game(width, height, title);
    
    game.run();
    
    return EXIT_SUCCESS;
}
