#include "WorldView.h"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

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
    
    glViewport(0, 0, mWindow->getSize().x, mWindow->getSize().y);
    
    //set up projection
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(mProjectionMatrix));
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