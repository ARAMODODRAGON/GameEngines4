#ifndef LOAD_OBJ_MODEL_H
#define LOAD_OBJ_MODEL_H

#include "Mesh.h"

class LoadOBJModel {

	std::vector<vec3> verticies;
	std::vector<vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<int> indices, normalIndices, texIndices;
	std::vector<Vertex> meshVerticies;
	std::vector<Submesh> submeshes;

	void PostProcessing();
	void LoadMaterial(const string& matName);
	void LoadMaterialLibrary(const string& matFilePath);

	GLuint currentTex;

public:

	LoadOBJModel();
	~LoadOBJModel();

	void OnDestory();

	void LoadModel(const string& objFilePath, const string& mtlFilePath);
	void LoadModel(const string& filepath);
	std::vector<Vertex> GetVerts() const { return meshVerticies; }
	std::vector<int> GetIndices() const { return indices; }
	std::vector<Submesh> GetSubmeshes() const { return submeshes; }

};

#endif // !LOAD_OBJ_MODEL_H