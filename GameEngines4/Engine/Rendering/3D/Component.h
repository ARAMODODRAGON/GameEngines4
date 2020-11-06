#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
class Camera;

class Component {

	GameObject* object;

public:

	Component();
	virtual ~Component() = 0;

	virtual void OnCreate() { }
	virtual void Update(const float& delta) { }
	virtual void Render(Camera* camera) { }
	virtual void OnDestroy() { }

	void SetObject(GameObject* object);
	GameObject* GetObject() const;

};

#endif // !COMPONENT_H