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

#include "../Block.h"
#include "Object.h"

typedef std::vector<std::vector<std::vector<std::shared_ptr<Block>>>> Blocks;
typedef std::vector<std::vector<std::shared_ptr<Block>>> xBlocks;
typedef std::vector<std::shared_ptr<Block>> yBlocks;
typedef std::shared_ptr<Block> zBlocks;

class Chunk : public Object {
public:
    Chunk(int size, std::shared_ptr<sf::RenderWindow> window);
    ~Chunk();
    
    virtual void update(float dt);
	virtual void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix);
	virtual void handle(sf::Event event);
    
    //size of the chunks
    void setChunkSize(int size);
    int getChunkSize();

	//model matrix
	glm::mat4 mModelMatrix;
    
private:
    //chunk size
    int mSize;
    std::shared_ptr<sf::RenderWindow> mWindow;
    Blocks mBlockArray;
};