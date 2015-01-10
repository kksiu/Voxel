//
//  Camera.h
//  Voxel
//
//  Created by Kenneth Siu on 1/10/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include <stdio.h>

#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::mat4 viewMatrix);
    ~Camera();
    
private:
    glm::mat4 mViewMatrix;
};