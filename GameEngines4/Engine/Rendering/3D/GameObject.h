#ifndef	GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject {
private:

	// model
	Model* model;

	// the transform
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	int modelInstance;

public:
	GameObject(Model* model_, const glm::vec3& pos = glm::vec3());
	~GameObject();

	void Render(Camera* camera);
	void Update(const float& delta);

	glm::vec3 GetPosition() const {
		return position;
		if (model) model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
	glm::vec3 GetRotation() const {
		return rotation;
		if (model) model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
	float GetAngle() const {
		return angle;
		if (model) model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
	glm::vec3 GetScale() const {
		return scale;
		if (model) model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}

	void SetPosition(const glm::vec3& pos) { position = pos; }
	void SetRotation(const glm::vec3& rot) { rotation = rot; }
	void SetAngle(const float& ang) { angle = ang; }
	void SetScale(const glm::vec3& s) { scale = s; }

private:

};

#endif // !GAMEOBJECT_H
