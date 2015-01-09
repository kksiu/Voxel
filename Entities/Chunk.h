//
//  Chunk.h
//  Voxel
//
//  Created by Kenneth Siu on 1/9/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Block.h"

typedef std::vector<std::vector<std::vector<std::shared_ptr<Block>>>> Blocks;
typedef std::vector<std::vector<std::shared_ptr<Block>>> xBlocks;
typedef std::vector<std::shared_ptr<Block>> yBlocks;
typedef std::shared_ptr<Block> zBlocks;

class Chunk {
public:
    Chunk(int size, std::shared_ptr<sf::RenderWindow> window);
    ~Chunk();
    
    void update(float dt);
    void render();
    
    //size of the chunks
    void setChunkSize(int size);
    int getChunkSize();
    
private:
    //chunk size
    int mSize;
    std::shared_ptr<sf::RenderWindow> mWindow;
    Blocks mBlockArray;
};