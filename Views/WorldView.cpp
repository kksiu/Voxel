#include "WorldView.h"

#include <iostream>

#include <GL/glew.h>

WorldView::WorldView(std::shared_ptr<sf::RenderWindow> window)
: mWindow(window)
{
}

WorldView::~WorldView()
{
}

void WorldView::render()
{
	glFrontFace(GL_CCW);

	// set up the camera for drawing!
	glEnable(GL_DEPTH_TEST);
}

void WorldView::update(float dt)
{

}

void WorldView::handle(sf::Event event)
{

}

void WorldView::dispose()
{

}