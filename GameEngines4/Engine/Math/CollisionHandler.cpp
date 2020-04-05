#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::Singleton = nullptr;
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();

CollisionHandler::CollisionHandler() {
	colliders.reserve(10);
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler() {
	//OnDestroy();
}

void CollisionHandler::OnCreate() {
	colliders.clear();
	prevCollisions.clear();
}

void CollisionHandler::AddObject(GameObject* go) {
	colliders.push_back(go);
}

void CollisionHandler::MouseUpdate(vec2 mousePos, int button) {
	Ray mouseRay = CollisionDetection::ScreenToWorldPosition(mousePos,
		CoreEngine::GetSingleton()->GetScreenSize(), CoreEngine::GetSingleton()->GetCamera());

	GameObject* result = nullptr;
	float shortestDistance = FLT_MAX;

	for (GameObject* g : colliders) {
		if (mouseRay.OBBCollision(g->GetBoundingBox())) {
			if (mouseRay.distance < shortestDistance) {
				result = g;
				shortestDistance = mouseRay.distance;
			}
		}
	}

	for (auto c : prevCollisions) {
		if (c != result && c != nullptr) {
			c->SetHit(false);
		}
		c = nullptr;
	}
	prevCollisions.clear();

	if (result) {
		result->SetHit(true);
		prevCollisions.push_back(result);
	}

}

void CollisionHandler::OnDestroy() {

	for (auto entry : colliders) {
		entry = nullptr;
	}
	colliders.clear();

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();

}
