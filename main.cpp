#include <GL/glew.h>

#include <SFML/Graphics.hpp>

#include "Game.h"

int main(int, char const**)
{
    //set the context of the window
    sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
    
    Game game(800, 600, "Hello", settings);
    
    game.run();
    
    return EXIT_SUCCESS;
}
