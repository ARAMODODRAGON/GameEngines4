#include "GLRenderer.h"
#include <glew.h>
#include "../../Core/Debug.h"

GLRenderer::GLRenderer() : context(nullptr){ }

GLRenderer::~GLRenderer() { }

SDL_Window* GLRenderer::CreateWindow(const uvec2& size, const string& title) {

	SetPreAttributes();

	// create window
	SDL_Window* window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		size.x,
		size.y,
		SDL_WINDOW_OPENGL
	);

	// failed to create window
	if (window == nullptr) return nullptr;

	// create context
	context = SDL_GL_CreateContext(window);

	SetPostAttributes();

	// check if it was created
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		DEBUG_ERROR("Failed to initialize GLEW");
		return nullptr;
	}

	// enable this shit
	glEnable(GL_DEPTH_TEST);

	// print graphics card and opengl version
	DEBUG_INFO("Graphics card: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
	DEBUG_INFO("OpenGL version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return window;
}

void GLRenderer::ClearScreen(const vec4& screenColor) { 
	// clear the screen
	glClearColor(screenColor.x, screenColor.y, screenColor.z, screenColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::SetPreAttributes() {
	// set attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// this matches to the refresh rate of the display
	SDL_GL_SetSwapInterval(1);

	// experimental? something something, yea!
	glewExperimental = GL_TRUE;
}

void GLRenderer::SetPostAttributes() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
