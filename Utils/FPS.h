//
//  FPS.h
//  SFML
//
//  Created by Kenneth Siu on 11/28/14.
//  Copyright (c) 2014 Kenneth Siu. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <SFML/System.hpp>

class FPS
{
public:
    FPS() : mFrame(0), mFps(0) {}
    
    inline void update();
    
    const unsigned int getFPS() const { return mFps; }
    
private:
    unsigned int mFrame;
    unsigned int mFps;
    sf::Clock mClock;
};

void FPS::update()
{
    if(mClock.getElapsedTime().asSeconds() >= 1.f)
    {
        mFps = mFrame;
        mFrame = 0;
        mClock.restart();
    }
    
    ++mFrame;
}