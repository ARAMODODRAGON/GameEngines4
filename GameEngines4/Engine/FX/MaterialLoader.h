#ifndef MATERIAL_LOADER_H
#define MATERIAL_LOADER_H

#include "../Graphics/MaterialHandler.h"
#include "../Graphics/TextureHandler.h"
#include <sstream>

class MaterialLoader {

	MaterialLoader() = delete;
	~MaterialLoader();

	// disable copy & move constructors/operators
	MaterialLoader(const MaterialLoader&) = delete;
	MaterialLoader(MaterialLoader&&) = delete;
	MaterialLoader& operator=(const MaterialLoader&) = delete;
	MaterialLoader& operator=(MaterialLoader&&) = delete;

	static GLuint LoadTexture(std::string filepath);

public:

	static void LoadMaterial(std::string filepath);


};

#endif // !MATERIAL_LOADER_H