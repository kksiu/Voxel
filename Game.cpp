//
//  Game.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/7/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Game.h"

#include <GL/glew.h>

Game::Game(unsigned int width,
           unsigned int height,
           std::string title,
           sf::ContextSettings settings)
{
    mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Default, settings);
    mMainInputHandler = std::make_shared<InputHandler>(mWindow);
	mViewManager = std::make_shared<ViewManager>(mWindow);
}

Game::~Game()
{
}

void Game::run()
{
	//enable GLEW
	glewInit();

	//Enable OpenGL functions
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.001f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //event to use
    sf::Event event;

	sf::Clock deltaClock;
    
    //run game while window is open
    while(mWindow->isOpen())
    {
        //check for events
        while(mWindow->pollEvent(event))
        {
            //handle events
            mMainInputHandler->handle(event);
			mViewManager->handle(event);
        }
        
        //update views
		float dt = deltaClock.restart().asSeconds();
		mViewManager->update(dt);

        //render window
        mWindow->clear();
        
        //render world
		mViewManager->render();
        
        //switch display buffers
        mWindow->display();
    }
}