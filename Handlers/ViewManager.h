#pragma once

#include <stdio.h>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../Views/View.h"

enum class ViewEnum
{
	World
};

class ViewManager {
public:
	ViewManager(std::shared_ptr<sf::RenderWindow> window);
	~ViewManager();

	void update(float dt);
	void render();
	void handle(sf::Event event);
	void setView(ViewEnum view);
	void pushView(ViewEnum view);
	void popView();

private:
	std::shared_ptr<sf::RenderWindow> mWindow;
	std::vector<std::shared_ptr<View>> viewStack;
	
	std::shared_ptr<View> getView(ViewEnum state);
};