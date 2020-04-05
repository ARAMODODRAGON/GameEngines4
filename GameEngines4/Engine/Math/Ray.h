#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
using namespace glm; // I give up
#include "BoundingBox.h"
#include "CollisionDetection.h"

struct Ray {

	vec3 position;
	vec3 direction;

	float distance;

	Ray() : position(0.0f), direction(0.0f), distance(0.0f) { }

	Ray(const vec3& position_, const vec3& direction_)
		: position(position_), direction(direction_), distance(0.0f) { }

	Ray& operator=(const Ray& other) {
		position = other.position;
		direction = other.direction;
		distance = 0.0f;
	}

	bool OBBCollision(const BoundingBox& box) {
		distance = -1.0f;
		return CollisionDetection::RayOBBIntersection(this, &box);
	}

};

#endif // !RAY_H