#ifndef GL_MESH_HPP
#define GL_MESH_HPP

#include "../Mesh.h"
#include <glew.h>

class GLMesh : public Mesh {
public:

	GLMesh(const Submesh& subMesh_, GLuint program);
	~GLMesh() final;

	virtual void Render(Camera* camera, std::vector<glm::mat4> instances);

private:

	// vertex object and vertex buffer
	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, proLoc, cameraPosLoc;
	GLuint lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColorLoc;
	GLuint matDiffuseMapLoc, matShinynessLoc, matTransparencyLoc, matAmbientLoc, matDiffuseLoc, matSpecularLoc;

	Submesh submesh;

	// creating the VAO and VBO
	void GenerateBuffers();
};

#endif // !GL_MESH_HPP