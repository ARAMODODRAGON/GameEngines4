#include "LoadOBJModel.h"
#include <sstream>
#include <algorithm>

using glm::vec2;

void LoadOBJModel::PostProcessing() {
	Vertex vert;
	for (size_t i = 0; i < indices.size(); ++i) {
		vert.position = verticies[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = texCoords[texIndices[i]];
		meshVerticies.push_back(vert);
	}

	Submesh submesh;
	submesh.verticies = meshVerticies;
	submesh.indices = indices;
	submesh.texID = currentTex;

	submeshes.push_back(submesh);

	indices.clear();
	normalIndices.clear();
	texIndices.clear();
	meshVerticies.clear();
	currentTex = 0;
}

void LoadOBJModel::LoadMaterial(const string& matName) {
	currentTex = TextureHandler::GetSingleton()->GetTexture(matName);

	if (currentTex == 0) {
		TextureHandler::GetSingleton()->CreateTexture(matName, "Resources/Textures/" + matName + ".jpg");
		currentTex = TextureHandler::GetSingleton()->GetTexture(matName);
		DEBUG_INFO("Texture was not found, now loading: " + matName + ".jpg");
	}
}

void LoadOBJModel::LoadMaterialLibrary(const string& matFilePath) {
	std::ifstream in(matFilePath.c_str(), std::ios::in);

	if (!in) {
		DEBUG_ERROR("failed to open file " + matFilePath);
		return;
	}

	string line;

	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			LoadMaterial(line.substr(7));
		}
	}
}

LoadOBJModel::LoadOBJModel() : currentTex(0) {
	verticies.reserve(200);
	normals.reserve(200);
	texCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	texIndices.reserve(200);
	meshVerticies.reserve(200);
	submeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel() { OnDestory(); }

void LoadOBJModel::OnDestory() {
	verticies.clear();
	normals.clear();
	texCoords.clear();
	indices.clear();
	normalIndices.clear();
	texIndices.clear();
	meshVerticies.clear();
	submeshes.clear();
}

void LoadOBJModel::LoadModel(const string& objFilePath, const string& mtlFilePath) {
	LoadMaterialLibrary(mtlFilePath);
	LoadModel(objFilePath);
}

void LoadOBJModel::LoadModel(const string& filepath) {
	std::ifstream in(filepath.c_str(), std::ios::in);

	if (!in) {
		DEBUG_ERROR("Cannot open obj file: " + filepath);
		return;
	}

	string line;

	while (std::getline(in, line)) {
		/// vertex data
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			vec3 vec;
			v >> vec.x >> vec.y >> vec.z;
			verticies.push_back(vec);
		}
		/// normal data
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream v(line.substr(3));
			vec3 vec;
			v >> vec.x >> vec.y >> vec.z;
			normals.push_back(vec);
		}
		/// texture data
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream v(line.substr(3));
			vec2 vec;
			v >> vec.x >> vec.y;
			texCoords.push_back(vec);
		}
		/// face data
		else if (line.substr(0, 2) == "f ") {
			// get a string where everything is seperated by spaces
			string s = line.substr(2);
			std::replace(s.begin(), s.end(), '/', ' ');

			// create substream
			std::stringstream v(s);

			int v0, t0, n0;
			int v1, t1, n1;
			int v2, t2, n2;

			v >> v0 >> t0 >> n0 >> v1 >> t1 >> n1 >> v2 >> t2 >> n2;

			indices.push_back(v0 - 1);
			indices.push_back(v1 - 1);
			indices.push_back(v2 - 1);
			texIndices.push_back(t0 - 1);
			texIndices.push_back(t1 - 1);
			texIndices.push_back(t2 - 1);
			normalIndices.push_back(n0 - 1);
			normalIndices.push_back(n1 - 1);
			normalIndices.push_back(n2 - 1);
		}
		// call post prossessing
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0)
				PostProcessing();
			
			LoadMaterial(line.substr(7));
		}
	}

	PostProcessing();
}
