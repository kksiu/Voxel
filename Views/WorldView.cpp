#include "WorldView.h"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

WorldView::WorldView(std::shared_ptr<sf::RenderWindow> window)
: mWindow(window), mPlayer(std::make_shared<Camera>(), window)
{
	float aspect = ((float)window->getSize().x) / ((float)window->getSize().y);
	mProjectionMatrix = glm::perspective(glm::radians(45.f), aspect, 1.f, 6000.f);
}

WorldView::~WorldView()
{
}

void WorldView::render()
{   
    glViewport(0, 0, mWindow->getSize().x, mWindow->getSize().y);
    
    //set up projection
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(mProjectionMatrix));

	//set up camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set the camera
	glMultMatrixf(glm::value_ptr(mPlayer.getCamera()));

	//render objects
	glColor3f(1.f, 0.f, 1.f);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.5f, -1.f);
	glVertex3f(0.5f, 0.5f, -1.f);
	glVertex3f(0.5f, -0.5f, -1.f);
	glVertex3f(-0.5f, -0.5f, -1.f);
	glEnd();
}

void WorldView::update(float dt)
{
	if (mWindow->hasFocus())
	{
		mPlayer.update(dt);
	}
}

void WorldView::handle(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
		{
			//close the window if pressed escape
			if (event.key.code == sf::Keyboard::Escape)
			{
				mWindow->close();
			}
		}

		default:
		{
			break;
		}
	}

	mPlayer.handle(event);
}

void WorldView::dispose()
{
}