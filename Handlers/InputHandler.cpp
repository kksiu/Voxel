//
//  InputHandler.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/8/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "InputHandler.h"

InputHandler::InputHandler(std::shared_ptr<sf::Window> window)
: mWindow(window)
{
}

InputHandler::~InputHandler()
{
    
}

void InputHandler::handle(sf::Event event)
{
    switch(event.type)
    {
        case sf::Event::Closed:
        {
            mWindow->close();
            break;
        }
            
        default:
        {
            break;
        }
    }
}