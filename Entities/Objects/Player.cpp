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

//set up the camera
Player::Player(std::shared_ptr<Camera> camera, std::shared_ptr<sf::RenderWindow> window) :
	mModelMatrix(),
	mCamera(camera),
	mWindow(window)
{
	sf::Mouse::setPosition(sf::Vector2i(mWindow->getSize().x / 2, mWindow->getSize().y / 2), *mWindow);
}

Player::~Player()
{
}

void Player::update(float dt)
{
	bool hasChanged = false;

	glm::vec3 translate(0.f, 0.f, 0.f);

	//get the front vector as well as the side vector
	glm::vec3 frontVec = mCamera->lookAt;
	frontVec = glm::normalize(frontVec);
	glm::vec3 sideVec = glm::cross(mCamera->lookUp, frontVec);
	sideVec = glm::normalize(sideVec);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		translate += (dt * frontVec);
		hasChanged = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		translate += (dt * sideVec);
		hasChanged = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		translate -= (dt * frontVec);
		hasChanged = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		translate -= (dt * sideVec);
		hasChanged = true;
	}

	if (hasChanged)
	{
		mCamera->translate(translate);
	}

	sf::Vector2i origPos = sf::Vector2i(mWindow->getSize().x / 2, mWindow->getSize().y / 2);
	sf::Vector2i newPos = sf::Mouse::getPosition(*mWindow);
	newPos -= origPos;

	//rotate based on these values
	mCamera->rotateDirection((float)newPos.x);
	mCamera->rotatePitch((float)newPos.y);

	sf::Mouse::setPosition(origPos, *mWindow);
}

void Player::render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix)
{

}

void Player::handle(sf::Event event)
{
}

glm::mat4 Player::getCamera()
{
	return mCamera->getCamera();
}