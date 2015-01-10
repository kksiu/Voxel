#pragma once

#include <stdio.h>
#include <memory>

#include "View.h"

class WorldView : public View{
public:
	WorldView(std::shared_ptr<sf::RenderWindow> window);
	~WorldView();

	virtual void render();
	virtual void update(float dt);
	virtual void handle(sf::Event event);
	virtual void dispose();

private:
	std::shared_ptr<sf::RenderWindow> mWindow;
};