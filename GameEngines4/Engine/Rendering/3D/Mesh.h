#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/TextureHandler.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 color;
};

struct Submesh {
	std::vector<Vertex> verticies;
	std::vector<int> indices;
	Material material;
};

class Mesh {
public:

	Mesh() { }
	virtual ~Mesh() = 0 { }
	virtual void Render(Camera* camera, std::vector<glm::mat4> instances) = 0;

};

#endif // !MESH_H
