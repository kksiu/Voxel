//
//  Game.h
//  Voxel
//
//  Created by Kenneth Siu on 1/7/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Handlers/InputHandler.h"
#include "Handlers/ViewManager.h"

#include "Utils/FPS.h"

class Game
{
public:
    Game(unsigned int width,
         unsigned int height,
         std::string title,
         sf::ContextSettings settings);
    ~Game();
    
    void run();
    
private:
    std::shared_ptr<sf::RenderWindow> mWindow;
    std::shared_ptr<InputHandler> mMainInputHandler;
	std::shared_ptr<ViewManager> mViewManager;

	//calculate FPS
	FPS fps;
};