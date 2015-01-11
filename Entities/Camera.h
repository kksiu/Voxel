//
//  Camera.h
//  Voxel
//
//  Created by Kenneth Siu on 1/10/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include <stdio.h>

#include <glm/glm.hpp>

#include <SFML/Window.hpp>

class Camera {
public:
    Camera();
    ~Camera();

	//this will translate the camera to a certain position
	void translate(glm::vec3 translate);

	//change pitch of camera (up and down)
	void rotatePitch(float rot);
	
	//change direction of camera (left and right)
	void rotateDirection(float rot);

	//returns the camera
	glm::mat4 getCamera();

	glm::vec3 lookFrom;
	glm::vec3 lookAt;
	glm::vec3 lookUp;
};