#ifndef WINDOW_H
#define WINDOW_H
// includes
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

class Window {
private:

	// variables
	int width, height;
	SDL_Window* window;
	SDL_GLContext context;

public:

	// oncreate and ondestroy
	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();

	// constructor & destructor
	Window() : width(0), height(0), window(nullptr), context(0) { }
	~Window() { OnDestroy(); }

	// getters
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	SDL_Window* GetWindow() const { return window; }

private:

	// attributes
	void SetPreAttributes();
	void SetPostAttributes();

};

#endif // !WINDOW_H