#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <glm/glm.hpp>

struct BoundingBox {
	glm::vec3 max, min;
	glm::mat4 transform;

	BoundingBox() : min(0.0f), max(0.0f), transform() { }

	BoundingBox(glm::vec3 max_, glm::vec3 min_, glm::mat4 transform_) 
		: max(max_), min(min_), transform(transform_) { }

};

#endif // !BOUNDING_BOX_H