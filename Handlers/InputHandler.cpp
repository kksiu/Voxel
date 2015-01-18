//
//  InputHandler.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/8/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "InputHandler.h"
#include "../Game.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
    
}

void InputHandler::handle(SDL_Event& event)
{
	//input handler will see when keys are pressed up or down
	switch (event.type)
	{
		case SDL_QUIT:
		{
			Game::isRunning = false;
			break;
		}

		case SDL_KEYDOWN:
		{
			mMapOfKeys[event.key.keysym.scancode] = true;
			break;
		}

		case SDL_KEYUP:
		{
			mMapOfKeys[event.key.keysym.scancode] = false;
			break;
		}

		default:
		{
			break;
		}
	}
}