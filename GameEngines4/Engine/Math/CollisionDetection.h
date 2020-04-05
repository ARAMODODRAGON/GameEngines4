#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "../Camera/Camera.h"

struct Ray;
struct BoundingBox;

class CollisionDetection {

	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator=(const CollisionDetection&) = delete;
	CollisionDetection& operator=(CollisionDetection&&) = delete;
	CollisionDetection() = delete;

public:

	static Ray ScreenToWorldPosition(vec2 mousePos, vec2 screenSize, Camera* camera);
	static bool RayOBBIntersection(Ray* ray, const BoundingBox* box);


};

#endif // !COLLISION_DETECTION_H