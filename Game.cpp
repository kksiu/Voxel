//
//  Game.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/7/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Game.h"

Game::Game(unsigned int width,
           unsigned int height,
           std::string title,
           sf::ContextSettings settings)
{
    mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Default, settings);
    
    mMainInputHandler = std::make_shared<InputHandler>(mWindow);
}

Game::~Game()
{
}

void Game::run()
{
    //event to use
    sf::Event event;
    
    //run game while window is open
    while(mWindow->isOpen())
    {
        //check for events
        while(mWindow->pollEvent(event))
        {
            //handle events
            mMainInputHandler->handle(event);
        }
        
        //update world
        
        //render window
        mWindow->clear();
        
        //render world
        
        //switch display buffers
        mWindow->display();
    }
}