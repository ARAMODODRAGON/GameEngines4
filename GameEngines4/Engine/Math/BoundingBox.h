#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <glm/glm.hpp>
using namespace glm;

struct BoundingBox {
	vec3 max, min;
	mat4 transform;

	BoundingBox() : min(0.0f), max(0.0f), transform() { }

	BoundingBox(vec3 max_, vec3 min_, mat4 transform_)
		: max(max_), min(min_), transform(transform_) { }

	bool Intersects(BoundingBox* other) {
		vec3 minCorner = GetTransformedPoint(min, transform);
		vec3 maxCorner = GetTransformedPoint(max, transform);

		vec3 otMinCorner = GetTransformedPoint(other->min, other->transform);
		vec3 otMaxCorner = GetTransformedPoint(other->max, other->transform);

		// these check if they are not overlapping
		if (minCorner.x > otMaxCorner.x || maxCorner.x < otMinCorner.x) return false;
		if (minCorner.y > otMaxCorner.y || maxCorner.y < otMinCorner.y) return false;
		if (minCorner.z > otMaxCorner.z || maxCorner.z < otMinCorner.z) return false;

		// if none of the previous statements return false then that means they are overlapping
		return true;
	}

private:

	vec3 GetTransformedPoint(vec3 point, mat4 transform) {
		return vec3(transform[3]) + point;
	}
};

#endif // !BOUNDING_BOX_H