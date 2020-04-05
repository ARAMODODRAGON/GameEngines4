#ifndef TEXTURE_HANDLER_H
#define TEXTURE_HANDLER_H
#include <memory>
#include <glew.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../Core/Debug.h"
using std::string;

struct Texture {
	GLuint textID = 0;
	float width = 0.0f;
	float height = 0.0f;
	string name = "";
};

class TextureHandler {

	#pragma region singleton

	static std::unique_ptr<TextureHandler> singleton;
	friend std::default_delete<TextureHandler>;

	TextureHandler();
	~TextureHandler();
	
	// disable copy & move constructors/operators
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator=(TextureHandler&&) = delete;
public:
	static TextureHandler* GetSingleton();
private:
	#pragma endregion

	static std::vector<Texture*> textures;

public:

	void CreateTexture(const string& name, const string& filepath);
	static const GLuint GetTexture(const string& name);
	static const Texture* GetTextureStruct(const string& name);
	void OnDestroy();
};

#endif // !TEXTURE_HANDLER_H