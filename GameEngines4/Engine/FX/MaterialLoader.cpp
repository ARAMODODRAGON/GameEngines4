#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() { }

GLuint MaterialLoader::LoadTexture(std::string filepath) {
	GLuint currentTex = TextureHandler::GetSingleton()->GetTexture(filepath);

	if (currentTex == 0) {
		TextureHandler::GetSingleton()->CreateTexture(filepath, "Resources/Textures/" + filepath + ".jpg");
		currentTex = TextureHandler::GetSingleton()->GetTexture(filepath);
		DEBUG_INFO("Texture was not found, now loading: " + filepath + ".jpg");
	}

	return currentTex;
}

void MaterialLoader::LoadMaterial(std::string filepath) {
	std::ifstream in(filepath.c_str(), std::ios::in);

	if (!in) {
		DEBUG_ERROR("failed to open file " + filepath);
		return;
	}

	Material mat;

	string line;

	while (std::getline(in, line)) {
		if (line.size() == 0) continue; // any other line should be 0 in size

		if (line.substr(0, 7) == "newmtl ") {
			if (mat.diffuseMap != 0) {
				MaterialHandler::GetSingleton()->AddMaterial(mat);
				mat = Material();
			}

			mat.name = line.substr(7);
			mat.diffuseMap = LoadTexture(mat.name);

		}
		if (line.substr(0, 3) == "\tNs") {
			std::stringstream ss(line.substr(3));

			ss >> mat.shinyness;

		}
		if (line.substr(0, 2) == "\td") {
			std::stringstream ss(line.substr(2));

			ss >> mat.transparency;

		}
		if (line.substr(0, 3) == "\tKa") {
			std::stringstream ss(line.substr(3));

			ss >> mat.ambient.r >> mat.ambient.g >> mat.ambient.b;

		}
		if (line.substr(0, 3) == "\tKd") {
			std::stringstream ss(line.substr(3));

			ss >> mat.diffuse.r >> mat.diffuse.g >> mat.diffuse.b;

		}
		if (line.substr(0, 3) == "\tKs") {
			std::stringstream ss(line.substr(3));

			ss >> mat.specular.r >> mat.specular.g >> mat.specular.b;

		}

	}

	if (mat.diffuseMap != 0)
		MaterialHandler::GetSingleton()->AddMaterial(mat);

	in.close();

}
