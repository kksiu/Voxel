//
//  Object.h
//  Voxel
//
//  Created by Kenneth Siu on 1/10/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#pragma once

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class Object {
public:
    virtual void update(float dt) = 0;
	virtual void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix) = 0;
    virtual void handle(sf::Event event) = 0;
    
    glm::mat4 mModelMatrix;
};