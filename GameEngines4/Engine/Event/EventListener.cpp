#include "EventListener.h"
#include "../Core/CoreEngine.h"

EventListener::~EventListener() { }

void EventListener::Update() { 
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		switch (e.type) {
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEWHEEL:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEMOTION: 
				MouseEventListener::Update(e);
				break;
			//case SDL_KEYDOWN: break;
			case SDL_QUIT:
				CoreEngine::GetSingleton()->Exit();
				break;

			default: break;
		}

	}
}
