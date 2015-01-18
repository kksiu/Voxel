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
#include <string>
#include <vector>

#include <GL/glew.h>
#include <SDL.h>

#include "../Block.h"
#include "Object.h"

typedef std::vector<std::vector<std::vector<std::shared_ptr<Block>>>> Blocks;
typedef std::vector<std::vector<std::shared_ptr<Block>>> xBlocks;
typedef std::vector<std::shared_ptr<Block>> yBlocks;

class Chunk : public Object {
public:
    Chunk(int size, std::string shader);
    ~Chunk();
    
    virtual void update(Uint32 dt);
    virtual void updateChunks();
	virtual void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix);
	virtual void handle(SDL_Event& event);
    
    //size of the chunks
    void setChunkSize(int size);
    int getChunkSize();

	//model matrix
	glm::mat4 mModelMatrix;
    
private:
    //chunk size
    unsigned int mSize;
    Blocks mBlockArray;
    
    //OPENGL
    //vertex buffer
    std::vector<glm::vec3> mVertexBuffer;
    GLuint mVertexBufferID;
    
    //normal buffer
    std::vector<glm::vec3> mNormalBuffer;
    GLuint mNormalBufferID;
    
    //shader information
    GLuint mShaderID;
    
    //view and projection matrix
    GLuint mProjID;
    GLuint mViewID;
};