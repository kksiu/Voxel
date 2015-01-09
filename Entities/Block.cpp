//
//  Block.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/9/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Block.h"

Block::Block() {
    mActive = false;
}

Block::~Block() {
    
}

void Block::setActive(bool active) {
    mActive = active;
}

bool Block::getActive() {
    return mActive;
}