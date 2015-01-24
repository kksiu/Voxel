//
//  Chunk.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/9/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Chunk.h"

#include "../../Handlers/ShaderManager.h"
#include "../../Utils/DrawHelper.h"

Chunk::Chunk(int size,
             std::string shader)
: mSize(size),
mModelMatrix(glm::mat4(1.f))
{
    //create the block array
    mBlockArray = Blocks();
    
    //iterate through all and make a block at each one
    for(int x = 0; x < size; x++)
    {
        mBlockArray.push_back(xBlocks());
        
        for(int y = 0; y < size; y++)
        {
            mBlockArray[x].push_back(yBlocks());
            
            for(int z = 0; z < size; z++)
            {
                mBlockArray[x][y].push_back(std::make_shared<Block>(true));
            }
        }
    }
    
    //load the shader
    mShaderID = ShaderManager::getInstance().getShader(shader);
    
    //set up a vertex buffer with the max size vertices
    //that would be 8 x size^3
    uint32_t maxSize = 6 * mSize * mSize * mSize;
    
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
    
    updateChunks();
}

Chunk::~Chunk()
{
}

void Chunk::update(Uint32 dt)
{
}

//based on what is active, update the current chunks
void Chunk::updateChunks()
{
    //check all active blocks and add them to the vertex buffer
    mVertexBuffer.clear();
    mNormalBuffer.clear();
    
    //last index
    unsigned int lastIndex = mSize - 1;
    
    for(size_t x = 0; x < mSize; x++)
    {
        for(size_t y = 0; y < mSize; y++)
        {
            for(size_t z = 0; z < mSize; z++)
            {
                //if the block is active, send to the vertex buffer
                if(!mBlockArray[x][y][z]->getActive())
                {
                    continue;
                }
                
                //set a bool for each side and see if it needs to be rendered
                bool top, bottom, left, right, front, back;
                top = bottom = left = right = front = back = false;
                
                //check top
                if((y == lastIndex) || (!mBlockArray[x][y+1][z]->getActive()))
                {
                    top = true;
                }
                
                //check bottom
                if((y == 0) || (!mBlockArray[x][y-1][z]->getActive()))
                {
                    bottom = true;
                }
                
                //check left
                if((x == 0) || (!mBlockArray[x-1][y][z]->getActive()))
                {
                    left = true;
                }
                
                //check right
                if((x == lastIndex) || (!mBlockArray[x+1][y][z]->getActive()))
                {
                    right = true;
                }
                
                //check front
                if((z == 0) || (!mBlockArray[x][y][z-1]->getActive()))
                {
                    front = true;
                }
                
                //check back
                if((z == lastIndex) || (!mBlockArray[x][y][z+1]->getActive()))
                {
                    back = true;
                }
                
                //if no need to render any side
                if(!(top || bottom || left || right || front || back))
                {
                    continue;
                }
                
                std::vector<std::vector<glm::vec3>> verticesAndNormals = DrawHelper::drawFaces(0.5f, glm::vec3(x, y, z), top, bottom, left, right, front, back);
                
                //add to vertex and normal buffer
                mVertexBuffer.insert(mVertexBuffer.end(), verticesAndNormals[0].begin(), verticesAndNormals[0].end());
                mNormalBuffer.insert(mNormalBuffer.end(), verticesAndNormals[1].begin(), verticesAndNormals[1].end());
                
            }
        }
    }
    
    GLsizeiptr size = mVertexBuffer.size() * sizeof(glm::vec3);
    
    //at the end, buffer data from both vertex and normal
    //so that they can be used the next time the chunk is rendered
    glBufferSubData(mVertexBufferID, 0, size, &mVertexBuffer[0]);
    glBufferSubData(mNormalBufferID, 0, size, &mNormalBuffer[0]);
    
    GLenum err = glGetError();
    
    if(err != GL_NO_ERROR)
    {
        printf("ERROR: %s\n", gluErrorString(err));
    }
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
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) (mVertexBuffer.size() * 3));
    
    //unbind vertex attribute arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    //unbind shader
    glUseProgram(0);
}

void Chunk::handle(SDL_Event& event)
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