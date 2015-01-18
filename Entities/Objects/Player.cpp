//
//  Player.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/10/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Player.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "../../Handlers/InputHandler.h"

//set up the camera
Player::Player(std::shared_ptr<Camera> camera, std::shared_ptr<SDL_Window> window) :
	mModelMatrix(),
	mCamera(camera),
	mWindow(window)
{
	SDL_GetWindowSize(window.get(), &width, &height);
	
	//set the width and height by 2 to get the center
	width /= 2;
	height /= 2;

	SDL_WarpMouseInWindow(window.get(), width, height);
}

Player::~Player()
{
}

void Player::update(Uint32 dt)
{
	float divide = 100000.f;

	bool hasChanged = false;

	glm::vec3 translate(0.f, 0.f, 0.f);

	//get the front vector as well as the side vector
	glm::vec3 frontVec = mCamera->lookAt;
	frontVec = glm::normalize(frontVec);
	glm::vec3 sideVec = glm::cross(mCamera->lookUp, frontVec);
	sideVec = glm::normalize(sideVec);

	if (InputHandler::getInstance().hasKey(SDL_SCANCODE_W))
	{
		translate += frontVec;
		hasChanged = true;
	}

	if (InputHandler::getInstance().hasKey(SDL_SCANCODE_A))
	{
		translate += sideVec;
		hasChanged = true;
	}

	if (InputHandler::getInstance().hasKey(SDL_SCANCODE_S))
	{
		translate -= frontVec;
		hasChanged = true;
	}

	if (InputHandler::getInstance().hasKey(SDL_SCANCODE_D))
	{
		translate -= sideVec;
		hasChanged = true;
	}


	if (hasChanged)
	{
		translate = glm::normalize(translate);
		translate *= (dt / divide);

		mCamera->translate(translate);
	}

	int nWidth, nHeight;
	SDL_GetMouseState(&nWidth, &nHeight);

	//get the distance between the two
	glm::vec2 newPos(nWidth - width, nHeight - height);

	//rotate based on these values
	mCamera->rotateDirection((float)newPos.x);
	mCamera->rotatePitch((float)newPos.y);

	SDL_WarpMouseInWindow(mWindow.get(), width, height);
}

void Player::render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix)
{

}

void Player::handle(SDL_Event& event)
{
}

glm::mat4 Player::getCamera()
{
	return mCamera->getCamera();
}