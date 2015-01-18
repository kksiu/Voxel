#pragma once

#include <stdio.h>
#include <memory>
#include <vector>

#include <SDL.h>

#include "../Views/View.h"

enum class ViewEnum
{
	World
};

class ViewManager {
public:
	ViewManager(std::shared_ptr<SDL_Window> window);
	~ViewManager();

	void update(Uint32 dt);
	void render();
	void handle(SDL_Event& event);
	void setView(ViewEnum view);
	void pushView(ViewEnum view);
	void popView();

private:
	std::shared_ptr<SDL_Window> mWindow;

	std::vector<std::shared_ptr<View>> viewStack;
	
	std::shared_ptr<View> getView(ViewEnum state);
};