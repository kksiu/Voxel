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

#include <SDL2/SDL.h>

#include "Handlers/InputHandler.h"
#include "Handlers/ViewManager.h"

class Game
{
public:
    Game(unsigned int width,
         unsigned int height,
         std::string title);
    ~Game();
    
    void run();

	static bool isRunning;
    
private:
    std::shared_ptr<SDL_Window> mWindow;
	std::shared_ptr<ViewManager> mViewManager;
    
    SDL_GLContext mainContext;
};