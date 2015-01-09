#include <SFML/Graphics.hpp>

#include "Game.h"

int main(int, char const**)
{
    //set the context of the window
    sf::ContextSettings settings;
    
    Game game(800, 600, "Hello", settings);
    
    game.run();
    
    return EXIT_SUCCESS;
}
