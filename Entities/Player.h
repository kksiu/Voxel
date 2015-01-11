//
//  Player.h
//  Voxel
//
//  Created by Kenneth Siu on 1/10/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <memory>

#include "Object.h"
#include "Camera.h"

//special type of camera which has 
class Player : public Object {
public:
	Player(std::shared_ptr<Camera> camera, std::shared_ptr<sf::RenderWindow> window);
	~Player();

	//Object functions
    virtual void update(float dt);
    virtual void render();
    virtual void handle(sf::Event event);
    
	//this will return the camera connected to this player
	virtual glm::mat4 getCamera();

    glm::mat4 mModelMatrix;

private:
	std::shared_ptr<Camera> mCamera;
	std::shared_ptr<sf::RenderWindow> mWindow;
};