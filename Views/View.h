#pragma once

#include <stdio.h>
#include <memory>

#include <SFML/Graphics.hpp>

#include "../Entities/Object.h"

class View {
public:
	virtual void render() = 0;
	virtual void update(float dt) = 0;
	virtual void handle(sf::Event event) = 0;
	virtual void dispose() = 0;

    std::vector<std::shared_ptr<Object>> mObjectList;
private:
	std::shared_ptr<sf::RenderWindow> mWindow;
};