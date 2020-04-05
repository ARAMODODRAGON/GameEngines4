#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "Ray.h"
#include "../Rendering/3D/GameObject.h"
#include <memory>

class CollisionHandler {

	static std::unique_ptr<CollisionHandler> Singleton;
	friend std::default_delete<CollisionHandler>;

	// disable copy & move constructors/operators for singleton
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;

	CollisionHandler();
	~CollisionHandler();

	static std::vector<GameObject*> colliders;
	static std::vector<GameObject*> prevCollisions;

public:

	static CollisionHandler* GetSingleton() {
		// check if instance exists
		if (Singleton.get() == nullptr) {
			Singleton.reset(new CollisionHandler());
		}

		// return singleton
		return Singleton.get();
	}

	void OnCreate();
	void AddObject(GameObject* go);
	void MouseUpdate(vec2 mousePos, int button);
	void OnDestroy();

};

#endif // !COLLISION_HANDLER_H