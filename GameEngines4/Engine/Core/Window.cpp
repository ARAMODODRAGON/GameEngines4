#include "Window.h"
#include "Debug.h"

bool Window::OnCreate(std::string name_, int width_, int height_, Renderer* renderer) {
	// initialize sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		DEBUG_ERROR("Failed to create window");
		return false;
	}

	// set window size
	width = width_;	height = height_;

	window = renderer->CreateWindow(uvec2(width, height), name_);

	// check if the window was created
	if (!window) {
		DEBUG_ERROR("Failed to create window");
		return false;
	}

	return true;
}

void Window::OnDestroy() {
	// destroy window
	if (window) SDL_DestroyWindow(window); 
	window = nullptr;

}

