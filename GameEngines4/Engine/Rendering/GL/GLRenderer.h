#ifndef GL_RENDERER_H
#define GL_RENDERER_H
#include "../Renderer.h"

class GLRenderer : public Renderer {
public:

	GLRenderer();
	~GLRenderer() final;

	virtual SDL_Window* CreateWindow(const uvec2& size, const string& title) override;
	virtual RendererType GetRendererType() override { return RendererType::OpenGL; }	

	virtual void ClearScreen(const vec4& screenColor);

private:

	// attributes
	void SetPreAttributes();
	void SetPostAttributes();

	SDL_GLContext context;
};

#endif // !GL_RENDERER_H