#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
using std::string;
#include "LoadOBJModel.h"

class Model {
private:
	// the meshes
	std::vector<Mesh*> subMeshes;
	GLuint shaderprogram;
	std::vector<glm::mat4> modelInstances;

	BoundingBox box;

public:
	Model(
		const string& objFilePath,
		const string& mtlFilePath,
		GLuint program
	);
	~Model();

	void Render(Camera* camera);
	void AddMesh(Mesh* mesh_);

	int CreateInstance(
		vec3 position,
		float angle,
		vec3 rotation,
		vec3 scale
	);
	void UpdateInstance(
		int index,
		vec3 position,
		float angle,
		vec3 rotation,
		vec3 scale
	);

	/// getters
	glm::mat4 GetModelMat(int index) const;
	BoundingBox GetBoundingBox() const { return box; }
	GLuint GetShaderProgram() const { return shaderprogram; }

private:

	glm::mat4 GetModelMat(
		vec3 position,
		float angle,
		vec3 rotation,
		vec3 scale
	) const;
	void LoadModel();

	LoadOBJModel* loadObj;

};

#endif // !MODEL_H
