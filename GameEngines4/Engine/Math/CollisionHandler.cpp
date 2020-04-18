#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::Singleton = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler() {
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler() {
	//OnDestroy();
}

void CollisionHandler::OnCreate(float worldsize) {
	prevCollisions.clear();
	scenePartition = new OctSpatialPartition(worldsize);
}

void CollisionHandler::AddObject(GameObject* go) {
	scenePartition->AddObject(go);
}

void CollisionHandler::MouseUpdate(vec2 mousePos, int button) {

	if (scenePartition != nullptr) {
		Ray mouseRay = CollisionDetection::ScreenToWorldPosition(mousePos,
			CoreEngine::GetSingleton()->GetScreenSize(), CoreEngine::GetSingleton()->GetCamera());

		GameObject* result = scenePartition->GetCollision(mouseRay);

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

	//for (GameObject* g : colliders) {
	//	if (mouseRay.OBBCollision(g->GetBoundingBox())) {
	//		if (mouseRay.distance < shortestDistance) {
	//			result = g;
	//			shortestDistance = mouseRay.distance;
	//		}
	//	}
	//}
	//
	//for (auto c : prevCollisions) {
	//	if (c != result && c != nullptr) {
	//		c->SetHit(false);
	//	}
	//	c = nullptr;
	//}
	//prevCollisions.clear();
	//
	//
	//
	//
	//
	//



}

void CollisionHandler::OnDestroy() {

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();

	delete scenePartition; scenePartition = nullptr;

}
