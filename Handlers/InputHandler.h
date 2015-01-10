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

#include <SFML/Graphics.hpp>

class InputHandler
{    
public:
    InputHandler(std::shared_ptr<sf::RenderWindow> window);
    ~InputHandler();
    
    //handle function
    void handle(sf::Event event);
    
private:
    std::shared_ptr<sf::RenderWindow> mWindow;
};