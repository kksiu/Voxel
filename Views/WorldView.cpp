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

WorldView::WorldView(std::shared_ptr<SDL_Window> window)
	: mPlayer(std::make_shared<Camera>(), window), testChunk(16, "RegularShader"), mWindow(window)
{
	SDL_GetWindowSize(window.get(), &width, &height);

	float aspect = ((float)width / (float)height);
	mProjectionMatrix = glm::perspective(glm::radians(45.f), aspect, 0.1f, 100.f);
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
    
    testChunk.render(mProjectionMatrix, camMatrix);
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