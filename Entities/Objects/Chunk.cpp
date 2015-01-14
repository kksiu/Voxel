//
//  Chunk.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/9/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Chunk.h"

#include "../../Handlers/ShaderManager.h"

Chunk::Chunk(int size,
             std::shared_ptr<sf::RenderWindow> window,
             std::string shader)
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
    
    //load the shader
    mShaderID = ShaderManager::getInstance().getGLShader(shader);
    
    //set up a vertex buffer with the max size vertices
    //that would be 8 x size^3
    uint32_t maxSize = 8 * mSize * mSize * mSize;
    
    //now that max size is known, generate a buffer
    glGenBuffers(1, &mVertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, maxSize,
                 NULL, GL_DYNAMIC_DRAW);
    
    glGenBuffers(1, &mNormalBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, mNormalBufferID);
    glBufferData(GL_ARRAY_BUFFER, maxSize, NULL, GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //get shader information of the projection and view matrix
    mProjID = glGetUniformLocation(mShaderID, "P");
    mViewID = glGetUniformLocation(mShaderID, "V");
}

Chunk::~Chunk()
{
}

void Chunk::update(float dt)
{
}

//based on what is active, update the current chunks
void Chunk::updateChunks()
{
    //check all active blocks and add them to the vertex buffer
    mVertexBuffer.clear();
    
    for(size_t i = 0; i < mSize; i++)
    {
        for(size_t j = 0; j < mSize; j++)
        {
            for(size_t k = 0; k < mSize; k++)
            {
                //if the block is active, send to the vertex buffer
                if(mBlockArray[i][j][k]->getActive())
                {
                    
                }
            }
        }
    }
    
    GLsizeiptr size = mVertexBuffer.size() * 3;
    
    //at the end, buffer data from both vertex and normal
    //so that they can be used the next time the chunk is rendered
    glBufferSubData(mVertexBufferID, 0, size, &mVertexBuffer[0]);
    glBufferSubData(mNormalBufferID, 0, size, &mNormalBuffer[0]);
}

void Chunk::render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix)
{
	//render the chunk
    //bind the shader
    glUseProgram(mShaderID);
    
    //set projection and view matrix
    glUniformMatrix4fv(mProjID, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(mViewID, 1, GL_FALSE, &viewMatrix[0][0]);
    
    //use vertex attribute arrays
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mNormalBufferID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    //use draw arrays to draw the chunk
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer.size() * 3);
    
    //unbind vertex attribute arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    //unbind shader
    glUseProgram(0);
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