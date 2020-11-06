#ifndef RENDERER_H
#define RENDERER_H
#include <inttypes.h>
#include <SDL.h>
#include <glm\glm.hpp>
using glm::uvec2;
using glm::vec4;
#include <string>
using std::string;

enum class RendererType : uint8_t {
	OpenGL
};

class Renderer {
public:

	Renderer() { }
	virtual ~Renderer() { }
	
	virtual SDL_Window* CreateWindow(const uvec2& size, const string& title) = 0;
	virtual RendererType GetRendererType() = 0;

	virtual void ClearScreen(const vec4& screenColor) = 0;
};

#endif // !RENDERER_H