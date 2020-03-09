#include "Mesh.h"
#include "../../Core/Debug.h"

Mesh::Mesh(const Submesh& subMesh_, GLuint program)
	: submesh(subMesh_), VAO(0), VBO(0), shaderProgram(program), modelLoc(0)
	, viewLoc(0), proLoc(0), textureLoc(0), cameraPosLoc(0), lightPosLoc(0), lightAmbientLoc(0)
	, lightDiffuseLoc(0), lightColorLoc(0) {
	GenerateBuffers();
}

Mesh::~Mesh() {
	// delete vao and vbo
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (submesh.verticies.size() > 0) {
		submesh.verticies.clear();
	}
	if (submesh.indices.size() > 0) {
		submesh.indices.clear();
	}
}

void Mesh::Render(Camera* camera, std::vector<glm::mat4> instances) {
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, submesh.texID);

	// set uniforms
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetView()));
	glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPersp()));
	glUniform3fv(cameraPosLoc, 1, glm::value_ptr(camera->GetPosition()));
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(camera->GetLightSourceList().front()->GetPosition()));
	glUniform1f(lightAmbientLoc, camera->GetLightSourceList().front()->GetAmbient());
	glUniform1f(lightDiffuseLoc, camera->GetLightSourceList().front()->GetDiffuse());
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(camera->GetLightSourceList().front()->GetColor()));

	// bind array
	glBindVertexArray(VAO);

	for (size_t i = 0; i < instances.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances[i]));
		// draw
		glDrawArrays(GL_TRIANGLES, 0, submesh.verticies.size());
	}


	// unbind
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() {
	// create vao and vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// set the buffer data
	glBufferData(GL_ARRAY_BUFFER, submesh.verticies.size() * sizeof(Vertex), &submesh.verticies[0], GL_STATIC_DRAW);

	// vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// vertex normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	// vertex color (temp)
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

	// cameraPosLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColorLoc
	// get uniforms
	glUseProgram(shaderProgram);
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	proLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "image");
	cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.position");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColorLoc = glGetUniformLocation(shaderProgram, "light.color");

	DEBUG_INFO("model:           " + TEXT(modelLoc));
	DEBUG_INFO("view:            " + TEXT(viewLoc));
	DEBUG_INFO("proj:            " + TEXT(proLoc));
	DEBUG_INFO("texture:         " + TEXT(textureLoc));
	DEBUG_INFO("cameraPosLoc:    " + TEXT(cameraPosLoc));
	DEBUG_INFO("lightPosLoc:     " + TEXT(lightPosLoc));
	DEBUG_INFO("lightAmbientLoc: " + TEXT(lightAmbientLoc));
	DEBUG_INFO("lightDiffuseLoc: " + TEXT(lightDiffuseLoc));
	DEBUG_INFO("lightColorLoc:   " + TEXT(lightColorLoc));

}
