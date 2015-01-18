#include "WorldView.h"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../Utils/DrawHelper.h"
#include "../Handlers/InputHandler.h"
#include "../Handlers/ShaderManager.h"
#include "../Game.h"

//test cube information
GLuint vertexBuffer;
GLuint normalBuffer;
GLuint shaderID;
GLuint pShader;
GLuint vShader;
std::vector<std::vector<glm::vec3>> cube;

WorldView::WorldView(std::shared_ptr<SDL_Window> window)
	: mPlayer(std::make_shared<Camera>(), window), testChunk(16, "Shader"), mWindow(window)
{
	SDL_GetWindowSize(window.get(), &width, &height);

	float aspect = ((float)width / (float)height);
	mProjectionMatrix = glm::perspective(glm::radians(45.f), aspect, 0.1f, 100.f);

	//anything below this is for debug purposes (drawing a test cube)
	cube = DrawHelper::drawFaces(.1f, glm::vec3(.0f, .0f, -2.f));

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, cube[0].size() * sizeof(glm::vec3), &cube[0][0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, cube[1].size() * sizeof(glm::vec3), &cube[1][0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//get shader
	shaderID = ShaderManager::getInstance().loadShader("Normal", "Shader");
	pShader = glGetUniformLocation(shaderID, "MVP");
}

WorldView::~WorldView()
{
}

void WorldView::render()
{
	glm::mat4 camMatrix = mPlayer.getCamera();

	//render everything in object list
	for (std::shared_ptr<Object> object : mObjectList)
	{
		object->render(mProjectionMatrix, camMatrix);
	}

	//DEBUG PURPOSES
	glUseProgram(shaderID);
	glUniformMatrix4fv(pShader, 1, GL_FALSE, &(mProjectionMatrix * camMatrix)[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(cube[0].size() * 3));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);
}

void WorldView::update(Uint32 dt)
{
	if (hasFocus)
	{
		mPlayer.update(dt);
	}
}

void WorldView::handle(SDL_Event& event)
{

	switch (event.type)
	{
		case SDL_KEYDOWN:
		{
			//close the window if pressed escape
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				Game::isRunning = false;
			}

			break;
		}

		case (SDL_WINDOWEVENT) :
		{
			switch (event.window.event)
			{
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				{
					hasFocus = true;
					break;
				}

				case SDL_WINDOWEVENT_FOCUS_LOST:
				{
					hasFocus = false;
					break;
				}
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