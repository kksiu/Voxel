//
//  Game.cpp
//  Voxel
//
//  Created by Kenneth Siu on 1/7/15.
//  Copyright (c) 2015 Kenneth Siu. All rights reserved.
//

#include "Game.h"

#include <iostream>

#include <GL/glew.h>

bool Game::isRunning = false;

Game::Game(unsigned int width,
           unsigned int height,
           std::string title)
{
	//init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = std::shared_ptr<SDL_Window>(SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1024,
		768,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),
		[](SDL_Window* window) { SDL_DestroyWindow(window); }
	);

	mainContext = SDL_GL_CreateContext(mWindow.get());
    
	//Initialize GLEW
	glewExperimental = GL_TRUE;

	GLenum glewError = glewInit();

	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
	}

	//error is when glew inits but it is normal
	GLenum glErr = glGetError();
	if (glErr != GL_NO_ERROR)
	{
		printf("ERROR: %s\n", gluErrorString(glErr));
	}

	mViewManager = std::make_shared<ViewManager>(mWindow);
}

Game::~Game()
{
}

void Game::run()
{
    //need to bind a vao for core profile
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
	//Enable OpenGL functions
	glEnable(GL_BLEND);
    
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//enable backface culling
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

	//enable CCW as front face
	glFrontFace(GL_CCW);

	// set up the camera for drawing!
	glEnable(GL_DEPTH_TEST);

    //event to use
    SDL_Event event;

	isRunning = true;

	Uint32 dt = SDL_GetTicks();
    
    //run game while window is open
    while(isRunning)
    {
        //check for events
        while(SDL_PollEvent(&event))
        {
            //handle events
            InputHandler::getInstance().handle(event);
			mViewManager->handle(event);
        }
        
        //update views
		dt = SDL_GetTicks() - dt;

		mViewManager->update(dt);

        //clear window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //render world
		mViewManager->render();
        
        //switch display buffers
		SDL_GL_SwapWindow(mWindow.get());
    }

	SDL_Quit();
}