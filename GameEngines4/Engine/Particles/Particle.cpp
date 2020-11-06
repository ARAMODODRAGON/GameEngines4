#include "Particle.h"
#include <glew.h>

Particle::Particle()
	: positionLoc(0), colourLoc(0), sizeLoc(0)
	, projLoc(0), viewLoc(0)
	, lifeTime(0.0f)
	, size(0.0f) { }

Particle::Particle(uint32_t shaderProgram_) : Particle() {
	GenerateBuffers(shaderProgram_);

}

Particle::~Particle() { }

void Particle::Render(Camera* camera_) {

	// safety
	glBindVertexArray(0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_PROGRAM_POINT_SIZE);

	// properties of the particle
	glUniform3f(positionLoc, position.x, position.y, position.z);
	glUniform4f(colourLoc, colour.r, colour.g, colour.b, colour.a);
	glUniform1f(sizeLoc, size);

	// camera mats
	mat4 persp = camera_->GetPersp();
	mat4 view = camera_->GetView();
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(persp));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glPointSize(size);

	glDrawArrays(GL_POINTS, 0, 1);

	glUseProgram(0);
	glDisable(GL_PROGRAM_POINT_SIZE);

}

void Particle::GenerateBuffers(uint32_t shaderProgram_) {

	glUseProgram(shaderProgram_);

	positionLoc = glGetUniformLocation(shaderProgram_, "position");
	colourLoc = glGetUniformLocation(shaderProgram_, "colour");
	sizeLoc = glGetUniformLocation(shaderProgram_, "size");

	projLoc = glGetUniformLocation(shaderProgram_, "proj");
	viewLoc = glGetUniformLocation(shaderProgram_, "view");

}

//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, textureID);
//
//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//struct Plane {
//	vec2 points;
//};
//
//static Plane points[] {
//	{vec2(-0.2f,0.2f)},
//	{vec2(0.2f,0.2f)},
//	{vec2(-0.2f,-0.2f)},
//	{vec2{0.2f - 0.2f}}
//};
//
//// set the buffer data
//glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Particle), points, GL_STATIC_DRAW);
//
//// set the buffer data
////glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Particle), verticies, GL_STATIC_DRAW);
//
//glm::mat4 ortho = camera_->GetOrtho();
//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));
//
//glUniform4f(colourLoc, colour.r, colour.g, colour.b, colour.a);
//
//glBindVertexArray(VAO);
//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

//// create & bind vao
//glGenVertexArrays(1, &VAO);
//glBindVertexArray(VAO);
//
//// create & bind VBO
//glGenBuffers(1, &VBO);
//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//// particle position
//glEnableVertexAttribArray(0);
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)0);
//
//// vertex normal
//glEnableVertexAttribArray(1);
//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, velocity));
//
////Colour
//glEnableVertexAttribArray(2);
//glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, colour));
