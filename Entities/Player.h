//
//  Player.h
//  Voxel
//
//  Created by Kenneth Siu on 1/10/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#pragma once

#include <stdio.h>

#include "Object.h"

class Player : public Object {
public:
    virtual void update(float dt);
    virtual void render();
    virtual void handle(sf::Event event);
    
    glm::mat4 mModelMatrix;
};