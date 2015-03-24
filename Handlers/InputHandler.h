//
//  InputHandler.h
//  Voxel
//
//  Created by Kenneth Siu on 1/8/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <memory>
#include <map>

#include <SDL2/SDL.h>

class InputHandler
{    
public:
    InputHandler();
    ~InputHandler();
    
    //handle function
    void handle(SDL_Event& event);

	static InputHandler& getInstance()
	{
		static InputHandler instance;
		return instance;
	}

	bool hasKey(SDL_Keycode keyCode)
	{
		return mMapOfKeys[keyCode];
	}
    
private:
	std::map<SDL_Keycode, bool> mMapOfKeys;
};