//
//  Camera.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/10/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Camera.h"

Camera::Camera(glm::mat4 viewMatrix)
: mViewMatrix(viewMatrix)
{
}

Camera::~Camera()
{
}