#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::singleton = nullptr;
std::vector<Texture*> TextureHandler::textures = std::vector<Texture*>();

TextureHandler::TextureHandler() {
	textures.reserve(10);
}

TextureHandler::~TextureHandler() {
	OnDestroy();
}

TextureHandler* TextureHandler::GetSingleton() {
	// check if instance exists and set it if it does not
	if (singleton.get() == nullptr)
		singleton.reset(new TextureHandler());
	// return singleton
	return singleton.get();
}

void TextureHandler::CreateTexture(const string& name, const string& filepath) {
	Texture* texture = new Texture();

	SDL_Surface* surface = nullptr;
	surface = IMG_Load(filepath.c_str());

	if (!surface) {
		DEBUG_ERROR("Could not find image: " + name + "at filepath:" + filepath);
		delete texture;
		return;
	}

	glGenTextures(1, &texture->textID);
	glBindTexture(GL_TEXTURE_2D, texture->textID);
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture->width = surface->w;
	texture->height = surface->h;
	texture->name = name;

	textures.push_back(texture);
}

const GLuint TextureHandler::GetTexture(const string& name) {
	for (Texture* tex : textures) {
		if (tex->name == name)
			return tex->textID;
	}
	return 0;
}

const Texture* TextureHandler::GetTextureStruct(const string& name) {
	for (Texture* tex : textures) {
		if (tex->name == name)
			return tex;
	}
	return nullptr;
}

void TextureHandler::OnDestroy() {
	if (textures.size() > 0) {
		for (Texture* tex : textures) {
			glDeleteTextures(sizeof(GLuint), &tex->textID);
			delete tex;
		}
		textures.clear();
	}
}
