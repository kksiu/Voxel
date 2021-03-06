#pragma once

#include <stdio.h>
#include <memory>

#include <glm/glm.hpp>

#include "View.h"
#include "../Entities/Objects/Player.h"
#include "../Entities/Objects/Chunk.h"

class WorldView : public View {
public:
	WorldView(std::shared_ptr<SDL_Window> window);
	~WorldView();

	virtual void render();
	virtual void update(Uint32 dt);
	virtual void handle(SDL_Event& event);
	virtual void dispose();

    std::vector<std::shared_ptr<Object>> mObjectList;
    
private:  
	std::shared_ptr<SDL_Window> mWindow;

    //projection matrix
    glm::mat4 mProjectionMatrix;

	//player, holding the camera
	Player mPlayer;
    
    Chunk testChunk;

	//width and height of window
	int width;
	int height;

	//used to see if window has focus
	bool hasFocus;
};