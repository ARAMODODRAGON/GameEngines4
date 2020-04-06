#ifndef	GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include <string>

class GameObject {
private:

	std::string name;

	// model
	Model* model;

	// the transform
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	int modelInstance;
	BoundingBox box;

	bool hit;

	void UpdateModel() {
		if (model) {
			model->UpdateInstance(modelInstance, position, angle, rotation, scale);
			box = model->GetBoundingBox();
			box.transform = model->GetModelMat(modelInstance);
		}
	}

public:
	GameObject(Model* model_, const glm::vec3& pos = glm::vec3());
	~GameObject();

	void Render(Camera* camera);
	void Update(const float& delta);

	glm::vec3 GetPosition() const {
		return position;
	}
	glm::vec3 GetRotation() const {
		return rotation;
	}
	float GetAngle() const {
		return angle;
	}
	glm::vec3 GetScale() const {
		return scale;
	}
	BoundingBox GetBoundingBox() const { return box; }
	std::string GetName() const { return name; }
	bool GetHit() const { return hit; }

	void SetPosition(const glm::vec3& pos) { position = pos; UpdateModel(); }
	void SetRotation(const glm::vec3& rot) { rotation = rot;  UpdateModel(); }
	void SetAngle(const float& ang) { angle = ang; UpdateModel(); }
	void SetScale(const glm::vec3& s) {
		scale = s; UpdateModel();
		box.min.x *= (scale.x > scale.x ? 1.0f : (scale.x * 0.5f));
		box.min.y *= (scale.y > scale.y ? 1.0f : (scale.y * 0.5f));
		box.max.x *= (scale.x > scale.x ? 1.0f : (scale.x * 0.5f));
		box.max.y *= (scale.y > scale.y ? 1.0f : (scale.y * 0.5f));
	}
	void SetName(const std::string name_) { name = name_; }
	void SetHit(const bool hit_) {
		hit = hit_;
		if (hit) { std::cout << "this object was hit (name: \"" + name + "\")" << std::endl; }
	}

private:

};

#endif // !GAMEOBJECT_H
