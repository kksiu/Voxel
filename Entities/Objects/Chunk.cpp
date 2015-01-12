//
//  Chunk.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/9/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Chunk.h"

Chunk::Chunk(int size,
             std::shared_ptr<sf::RenderWindow> window)
: mSize(size),
mWindow(window)
{
    //create the block array
    mBlockArray = Blocks();
    
    //iterate through all and make a block at each one
    for(int i = 0; i < size; i++)
    {
        mBlockArray.push_back(xBlocks());
        
        for(int j = 0; i < size; j++)
        {
            mBlockArray[i].push_back(yBlocks());
            
            for(int z = 0; i < size; z++)
            {
                mBlockArray[i][j].push_back(zBlocks());
            }
        }
    }
}

Chunk::~Chunk()
{
}

void Chunk::update(float dt)
{
}

void Chunk::render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix)
{
	//render the chunk

}

void Chunk::handle(sf::Event event)
{

}

void Chunk::setChunkSize(int size)
{
    mSize = size;
}

int Chunk::getChunkSize()
{
    return mSize;
}