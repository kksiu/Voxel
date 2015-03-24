#pragma once

#include <stdio.h>
#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "../Entities/Objects/Object.h"

class View {
public:
	virtual void render() = 0;
	virtual void update(Uint32 dt) = 0;
	virtual void handle(SDL_Event& event) = 0;
	virtual void dispose() = 0;

    std::vector<std::shared_ptr<Object>> mObjectList;
};