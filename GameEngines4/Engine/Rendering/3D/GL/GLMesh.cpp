#include "GLMesh.h"

GLMesh::GLMesh(const Submesh& subMesh_, GLuint program)
	: submesh(subMesh_)
	, VAO(0)
	, VBO(0)
	, shaderProgram(program)
	, modelLoc(0)
	, viewLoc(0)
	, proLoc(0)
	, cameraPosLoc(0)
	, lightPosLoc(0)
	, lightAmbientLoc(0)
	, lightDiffuseLoc(0)
	, lightColorLoc(0)
	, matDiffuseMapLoc(0)
	, matShinynessLoc(0)
	, matTransparencyLoc(0)
	, matAmbientLoc(0)
	, matDiffuseLoc(0)
	, matSpecularLoc(0) {
	GenerateBuffers();
}

GLMesh::~GLMesh() {
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

void GLMesh::Render(Camera* camera, std::vector<glm::mat4> instances) {
	glUniform1i(matDiffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, submesh.material.diffuseMap);

	// set uniforms

	/// matricies
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetView()));
	glUniformMatrix4fv(proLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPersp()));

	/// camera
	glUniform3fv(cameraPosLoc, 1, glm::value_ptr(camera->GetPosition()));

	/// light
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(camera->GetLightSourceList().front()->GetPosition()));
	glUniform1f(lightAmbientLoc, camera->GetLightSourceList().front()->GetAmbient());
	glUniform1f(lightDiffuseLoc, camera->GetLightSourceList().front()->GetDiffuse());
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(camera->GetLightSourceList().front()->GetColor()));

	/// material
	glUniform1f(matShinynessLoc, submesh.material.shinyness);
	glUniform1f(matTransparencyLoc, submesh.material.transparency);
	glUniform3f(matAmbientLoc, submesh.material.ambient.r, submesh.material.ambient.g, submesh.material.ambient.b);
	glUniform3f(matDiffuseLoc, submesh.material.diffuse.r, submesh.material.diffuse.g, submesh.material.diffuse.b);
	glUniform3f(matSpecularLoc, submesh.material.specular.r, submesh.material.specular.g, submesh.material.specular.b);

	// bind array
	glBindVertexArray(VAO);

	for (size_t i = 0; i < instances.size(); i++) {
		// check if it should be drawn
		vec4 notScreenPos = camera->GetPersp() * camera->GetView() * instances[i][3];
		vec3 screenpos = vec3(notScreenPos.x, notScreenPos.y, notScreenPos.z) / notScreenPos.w;
		if (screenpos.x < -1.0f || screenpos.x > 1.0f || screenpos.y < -1.0f || screenpos.y > 1.0f || screenpos.z < -1.0f || screenpos.z > 1.0f) {
			//std::cout << "not drawing " << std::endl;
			//std::cout << glm::to_string(screenpos) << std::endl;
			continue;
		}



		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances[i]));
		// draw
		glDrawArrays(GL_TRIANGLES, 0, submesh.verticies.size());
	}


	// unbind
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLMesh::GenerateBuffers() {
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
	cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.position");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColorLoc = glGetUniformLocation(shaderProgram, "light.color");

	matDiffuseMapLoc = glGetUniformLocation(shaderProgram, "mat.diffuseMap");
	matShinynessLoc = glGetUniformLocation(shaderProgram, "mat.shinyness");
	matTransparencyLoc = glGetUniformLocation(shaderProgram, "mat.transparency");
	matAmbientLoc = glGetUniformLocation(shaderProgram, "mat.ambient");
	matDiffuseLoc = glGetUniformLocation(shaderProgram, "mat.diffuse");
	matSpecularLoc = glGetUniformLocation(shaderProgram, "mat.specular");

	DEBUG_INFO("model:           " + TEXT(modelLoc));
	DEBUG_INFO("view:            " + TEXT(viewLoc));
	DEBUG_INFO("proj:            " + TEXT(proLoc));
	DEBUG_INFO("cameraPosLoc:    " + TEXT(cameraPosLoc));
	DEBUG_INFO("lightPosLoc:     " + TEXT(lightPosLoc));
	DEBUG_INFO("lightAmbientLoc: " + TEXT(lightAmbientLoc));
	DEBUG_INFO("lightDiffuseLoc: " + TEXT(lightDiffuseLoc));
	DEBUG_INFO("lightColorLoc:   " + TEXT(lightColorLoc));

	DEBUG_INFO("diffuseMap:		      " + TEXT(matDiffuseMapLoc));
	DEBUG_INFO("matShinynessLoc:	  " + TEXT(matShinynessLoc));
	DEBUG_INFO("matTransparencyLoc:   " + TEXT(matTransparencyLoc));
	DEBUG_INFO("matAmbientLoc:        " + TEXT(matAmbientLoc));
	DEBUG_INFO("matDiffuseLoc:        " + TEXT(matDiffuseLoc));
	DEBUG_INFO("matSpecularLoc:       " + TEXT(matSpecularLoc));

}

