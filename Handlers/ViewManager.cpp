#include "ViewManager.h"
#include "../Views/WorldView.h"

ViewManager::ViewManager(std::shared_ptr<sf::RenderWindow> window)
: mWindow(window), viewStack()
{
	pushView(ViewEnum::World);
}

ViewManager::~ViewManager()
{

}

void ViewManager::update(float dt)
{
	viewStack.back()->update(dt);
}

void ViewManager::render()
{
	for (std::shared_ptr<View> view : viewStack)
	{
		view->render();
	}
}

void ViewManager::handle(sf::Event event)
{
	for (std::shared_ptr<View> view : viewStack)
	{
		view->handle(event);
	}
}

void ViewManager::setView(ViewEnum view)
{
	popView();
	pushView(view);
}

void ViewManager::pushView(ViewEnum view)
{
	viewStack.push_back(getView(view));
}

void ViewManager::popView()
{
	//dispose of the latest view
	//and then remove from the stack
	std::shared_ptr<View> view = viewStack.back();
	view->dispose();
	
	viewStack.pop_back();
}

std::shared_ptr<View> ViewManager::getView(ViewEnum view)
{
	if (view == ViewEnum::World)
	{
		return std::make_shared<WorldView>(mWindow);
	}

	return NULL;
}