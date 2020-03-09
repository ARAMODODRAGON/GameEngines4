#include "Model.h"

Model::Model(
	const string& objFilePath, 
	const string& mtlFilePath, 
	GLuint program
)
	: subMeshes(std::vector<Mesh*>())
	, shaderprogram(program)
	, loadObj(nullptr)
{
	// reserve some memory for the submeshes
	subMeshes.reserve(10);
	modelInstances.reserve(5);
	loadObj = new LoadOBJModel();
	loadObj->LoadModel(objFilePath, mtlFilePath);
	this->LoadModel();
}

Model::~Model() {
	if (subMeshes.size() > 0) {
		for (unsigned int i = 0; i < subMeshes.size(); ++i) {
			delete subMeshes[i]; subMeshes[i] = nullptr;
		}
	}
	if (modelInstances.size() > 0) {
		modelInstances.clear();
	}
}

void Model::Render(Camera* camera) {
	if (subMeshes.size() > 0) {

		glUseProgram(shaderprogram);
		for (unsigned int i = 0; i < subMeshes.size(); ++i) {
			subMeshes[i]->Render(camera, modelInstances);
		}
		glUseProgram(0);
	}
}

void Model::AddMesh(Mesh* mesh_) {
	subMeshes.push_back(mesh_);
}

int Model::CreateInstance(vec3 position, float angle, vec3 rotation, vec3 scale) {
	modelInstances.push_back(GetModelMat(position, angle, rotation, scale));

	return modelInstances.size() - 1;
}

void Model::UpdateInstance(int index, vec3 position, float angle, vec3 rotation, vec3 scale) { 
	if (index < 0 || index >= modelInstances.size()) {
		DEBUG_ERROR("index was out of range");
		return;
	}
	modelInstances[index] = GetModelMat(position, angle, rotation, scale);
}

glm::mat4 Model::GetModelMat(int index) const {
	if (index < 0 || index >= modelInstances.size()) {
		DEBUG_ERROR("index was out of range");
		return glm::mat4();
	}
	return modelInstances[index];
}

glm::mat4 Model::GetModelMat(
	vec3 position, 
	float angle, 
	vec3 rotation, 
	vec3 scale
) const {
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotation);
	model = glm::scale(model, scale);
	return model;
}

void Model::LoadModel() { 
	for (size_t i = 0; i < loadObj->GetSubmeshes().size(); ++i) {
		subMeshes.push_back(new Mesh(loadObj->GetSubmeshes()[i], shaderprogram));
	}
	delete loadObj;
	loadObj = nullptr;
}
