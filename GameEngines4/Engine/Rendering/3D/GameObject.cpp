#include "GameObject.h"

void GameObject::UpdateModel() {
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box = model->GetBoundingBox();
		box.transform = model->GetModelMat(modelInstance);

		if (name == "apple") {
			//mat4 translate = glm::translate(mat4(), position);


			//printf("%s position: %f %f %f\n", name.c_str(), box.transform[3].x, box.transform[3].y, box.transform[3].z);
			//printf("%s position: %f %f %f\n", name.c_str(), position.x, position.y, position.z);
			//printf("%s position: %f %f %f\n", name.c_str(), translate[3].x, translate[3].y, translate[3].z);
		}
	}
}

GameObject::GameObject(Model* model_, const glm::vec3& pos)
	: model(model_)
	, position(pos)
	, angle(0.0f)
	, rotation(0.0f, 1.0f, 0.0f)
	, scale(1.0f)
	, modelInstance(0)
	, hit() {
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		UpdateModel();
	}
}

GameObject::~GameObject() {
	// delete components
	for (Component* c : components) {
		c->OnDestroy();
		delete c;
	}
	components.clear();
	// delete the model if there is one
	model = nullptr;
}

void GameObject::Render(Camera* camera) {
	for (Component* c : components) {
		c->Render(camera);
	}
}

void GameObject::Update(const float& delta) {
	// set angle updates the model
	SetAngle(GetAngle() + 0.5f * delta);

	// do at end
	for (Component* c : components) {
		c->Update(delta);
	}
}
