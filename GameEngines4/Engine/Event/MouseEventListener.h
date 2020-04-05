#ifndef EVENT_MOUSE_EVENT_LISTENER_H
#define EVENT_MOUSE_EVENT_LISTENER_H
#include <SDL.h>
#include <glm/glm.hpp>
class CoreEngine;

class MouseEventListener {

	static CoreEngine* engine;
	static glm::vec2 mousePos, preMousePos;

	static void UpdateMousePos();

public:
	// disable copy & move constructors/operators
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	MouseEventListener() = delete;
	~MouseEventListener();

	static void RegisterEngineObject(CoreEngine* engine);
	static void Update(SDL_Event e);

	static void NotifyOfMousePressed(int buttonType);
	static void NotifyOfMouseReleased(int buttonType);
	static void NotifyOfMouseScroll(int scroll);
	static void NotifyOfMouseMove();

	static glm::vec2 GetPreMousePos() { return preMousePos; }
	static glm::vec2 GetMousePos() { return mousePos; }
	static glm::vec2 GetMouseOffset() { return glm::vec2(mousePos.x - preMousePos.x, mousePos.y - preMousePos.y); }
};

#endif // !EVENT_MOUSE_EVENT_LISTENER_H