//
//  Camera.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/10/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

Camera::Camera()
: lookFrom(0.f, 0.f, 0.f), lookAt(0.f, 0.f, -1.f), lookUp(0.f, 1.f, 0.f)
{
}

Camera::~Camera()
{
}

void Camera::translate(glm::vec3 translate)
{
	lookFrom += translate;
}

void Camera::rotatePitch(float rot)
{
	//rotates the up direction
	glm::vec3 sideVec = glm::cross(lookUp, lookAt);
	lookAt = glm::rotate(lookAt, rot * 0.01f, sideVec);
	lookUp = glm::cross(lookAt, sideVec);
}

void Camera::rotateDirection(float rot)
{
	//rotates direction
	lookAt = glm::rotate(lookAt, -rot * 0.01f, glm::vec3(0, 1, 0));
	lookUp = glm::rotate(lookUp, -rot * 0.01f, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getCamera()
{
	return glm::lookAt(lookFrom, lookFrom + lookAt, lookUp);
}