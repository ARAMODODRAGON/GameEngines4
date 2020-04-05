#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engine = nullptr;
glm::vec2 MouseEventListener::mousePos = glm::vec2(0.0f);
glm::vec2 MouseEventListener::preMousePos = glm::vec2(0.0f);

void MouseEventListener::UpdateMousePos() {

	glm::ivec2 tmp;

	SDL_GetMouseState(&tmp.x, &tmp.y);

	tmp.y = engine->GetScreenSize().y - tmp.y;

	static bool firstUpdate = true;
	if (firstUpdate) {
		firstUpdate = false;

		preMousePos = mousePos = tmp;
	} else {
		preMousePos = mousePos;
		mousePos = tmp;
	}
}

MouseEventListener::~MouseEventListener() {
	engine = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_) {
	engine = engine_;
}

void MouseEventListener::Update(SDL_Event e) {
	switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			UpdateMousePos();
			NotifyOfMousePressed(e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			UpdateMousePos();
			NotifyOfMouseReleased(e.button.button);
			break;
		case SDL_MOUSEMOTION:
			UpdateMousePos();
			NotifyOfMouseMove();
			break;
		case SDL_MOUSEWHEEL:
			UpdateMousePos();
			NotifyOfMouseScroll(e.wheel.y);
			break;
		default:
			break;
	}

}

void MouseEventListener::NotifyOfMousePressed(int buttonType) {
	if (engine) engine->NotifyOfMousePressed(mousePos);
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType) {
	if (engine) engine->NotifyOfMouseReleased(mousePos, buttonType);
}

void MouseEventListener::NotifyOfMouseScroll(int scroll) {
	if (engine) engine->NotifyOfMouseScroll(scroll);
}

void MouseEventListener::NotifyOfMouseMove() {
	if (engine) engine->NotifyOfMouseMove(mousePos);
}
