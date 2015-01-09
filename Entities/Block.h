//
//  Block.h
//  Voxel
//
//  Created by Kenneth Siu on 1/9/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#pragma once

#include <stdio.h>

enum class BlockType {
    Default
};

//this will be a singular block
//includes any block in the world
class Block {
public:
    Block();
    ~Block();
    
    void setActive(bool active);
    bool getActive();
    
private:
    bool mActive;
};