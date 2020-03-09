#include "GameObject.h"

GameObject::GameObject(Model* model_, const glm::vec3& pos)
	: model(model_)
	, position(pos)
	, angle(0.0f)
	, rotation(0.0f, 1.0f, 0.0f)
	, scale(1.0f)
	, modelInstance(0) {
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::~GameObject() {
	// delete the model if there is one
	if (model) delete model;
	model = nullptr;
}

void GameObject::Render(Camera* camera) {
	// render the model if there is one
	if (model) model->Render(camera);
}

void GameObject::Update(const float& delta) {
	angle += 0.5f * delta;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, vec3(0.0f, 1.0f, 0.0f), vec3(1.0f));
	}
}
