#ifndef WINDOW_H
#define WINDOW_H
// includes
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "../Rendering/Renderer.h"

class Window {
private:

	// variables
	int width, height;
	SDL_Window* window;

public:

	// oncreate and ondestroy
	bool OnCreate(std::string name_, int width_, int height_, Renderer* renderer);
	void OnDestroy();

	// constructor & destructor
	Window() : width(0), height(0), window(nullptr) { }
	~Window() { OnDestroy(); }

	// getters
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	SDL_Window* GetWindow() const { return window; }

};

#endif // !WINDOW_H