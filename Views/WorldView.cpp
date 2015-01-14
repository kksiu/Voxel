#include "WorldView.h"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../Utils/DrawHelper.h"

WorldView::WorldView(std::shared_ptr<sf::RenderWindow> window)
: mWindow(window), mPlayer(std::make_shared<Camera>(), window)
{
	float aspect = ((float)window->getSize().x) / ((float)window->getSize().y);
	mProjectionMatrix = glm::perspective(glm::radians(45.f), aspect, 0.1f, 100.f);
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

//    GLfloat lightpos[] = {.5, 1., 0.5, 1.};
//    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    
	//set up camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set the camera
	glm::mat4 camMatrix = mPlayer.getCamera();
	glMultMatrixf(glm::value_ptr(camMatrix));

	//render objects
	glColor3f(1.f, 0.f, 1.f);
	
	//test cube
    std::vector<std::vector<glm::vec3>> cube = DrawHelper::drawFaces(.1f, glm::vec3(0.f));

	glBegin(GL_TRIANGLES);

    for (size_t i = 0; i < cube[0].size(); i++)
	{
        glNormal3fv(glm::value_ptr(cube[1][i]));
		glVertex3fv(glm::value_ptr(cube[0][i]));
    }

	glEnd();

	//render everything in object list
	for (std::shared_ptr<Object> object : mObjectList)
	{
		object->render(mProjectionMatrix, camMatrix);
	}
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

			break;
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