#ifndef	GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include <string>
#include "Component.h"
#include <vector>

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

	std::vector<Component*> components;

	void UpdateModel();

public:
	GameObject(Model* model_, const glm::vec3& pos = glm::vec3());
	~GameObject();

	void Render(Camera* camera);
	void Update(const float& delta);

	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetRotation() const { return rotation; }
	float GetAngle() const { return angle; }
	glm::vec3 GetScale() const { return scale; }
	BoundingBox GetBoundingBox() const { return box; }
	std::string GetName() const { return name; }
	bool GetHit() const { return hit; }

	void SetPosition(const glm::vec3& pos) { position = pos; UpdateModel(); }
	void SetRotation(const glm::vec3& rot) { rotation = rot;  UpdateModel(); }
	void SetAngle(const float& ang) { angle = ang; UpdateModel(); }
	void SetScale(const glm::vec3& s) {
		scale = s; UpdateModel();
		//box.min *= (scale.x > 1.0f ? 1.0f : (scale.x * 0.5f));
		//box.max *= (scale.x > 1.0f ? 1.0f : (scale.x * 0.5f));
		box.min *= scale;
		box.max *= scale;
	}
	void SetName(const std::string name_) { name = name_; }
	void SetHit(const bool hit_) {
		hit = hit_;
		if (hit) { std::cout << "this object was hit (name: \"" + name + "\")" << std::endl; }
	}

	template<class T, class... Args>
	T* AddComponent(Args&&... args) {
		// first check if the component already exists and return it
		if (T* comp = GetComponent<T>())
			return comp;

		// create a new T instance, unpack any arguments
		T* comp = new T(std::forward<Args>(args)...);

		// it is a component add it
		if (Component* c = dynamic_cast<Component*>(comp)) {
			components.push_back(c);
			c->SetObject(this);
			c->OnCreate();
			return comp;
		} 
		// it isnt a component delete it
		else {
			delete comp;
			DEBUG_ERROR("T was not a type of component");
			return nullptr;
		}
	}

	template<class T>
	T* GetComponent() {
		for (size_t i = 0; i < components.size(); ++i) {
			if (T* comp = dynamic_cast<T*>(components[i])) {
				return comp;
			}
		}
		return nullptr;
	}

	template<class T>
	bool DestroyComponent() {
		for (auto it = components.begin(); it != components.end(); ++it) {
			if (T* comp = dynamic_cast<T*>(*it)) {
				Component* c = *it;
				c->OnDestroy();
				delete c;
				c = nullptr;
				components.erase(it);
				return true;
			}
		}
		return false;
	}

private:

};

#endif // !GAMEOBJECT_H