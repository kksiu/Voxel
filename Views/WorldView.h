#pragma once

#include <stdio.h>
#include <memory>

#include <glm/glm.hpp>

#include "View.h"

class WorldView : public View{
public:
	WorldView(std::shared_ptr<sf::RenderWindow> window);
	~WorldView();

	virtual void render();
	virtual void update(float dt);
	virtual void handle(sf::Event event);
	virtual void dispose();

    std::vector<std::shared_ptr<Object>> mObjectList;
    
private:
	std::shared_ptr<sf::RenderWindow> mWindow;
    
    //projection matrix
    glm::mat4 mProjectionMatrix;
};