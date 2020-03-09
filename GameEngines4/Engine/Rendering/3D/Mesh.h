#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/TextureHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 color;
};

struct Submesh {
	std::vector<Vertex> verticies;
	std::vector<int> indices;
	GLuint texID;
};

class Mesh {
private:
	// vertex object and vertex buffer
	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, proLoc, textureLoc, cameraPosLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColorLoc;

	Submesh submesh;

public:
	Mesh(const Submesh& subMesh, GLuint program);
	~Mesh();
	void Render(Camera* camera, std::vector<glm::mat4> instances);

private:
	// creating the VAO and VBO
	void GenerateBuffers();
};

#endif // !MESH_H
