#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_)
	: shaderProgram(shaderProgram_)
	, textureID(textureID_)
	, VAO(NULL)
	, VBO(NULL)
	, modelLoc(NULL)
	, projLoc(NULL)
	, colourLoc(NULL)
	, textureLoc(NULL)
	, lifeTime(0.0f)
	, size(0.0f)
{
	GenerateBuffers();

}

Particle::~Particle()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Particle::Render(Camera* camera_)																																																																
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	struct Plane {
		vec2 points;
	};

	Plane points[]{
		{vec2(-0.2f,0.2f)},
		{vec2(0.2f,0.2f)},
		{vec2(-0.2f,-0.2f)},
		{vec2{0.2f - 0.2f}}
	};

	// set the buffer data
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Particle), points, GL_STATIC_DRAW);
	
	// set the buffer data
	//glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Particle), verticies, GL_STATIC_DRAW);
	
	glm::mat4 ortho = camera_->GetOrtho();
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));

	glUniform4f(colourLoc, colour.r, colour.g, colour.b, colour.a);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	
}

void Particle::GenerateBuffers()
{
	// create vao and vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	

	

	// particle position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)0);

	// vertex normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, velocity));

	//Colour
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, colour));

	glUseProgram(shaderProgram);
	//modelLoc = glGetUniformLocation(shaderProgram, "model");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	colourLoc = glGetUniformLocation(shaderProgram, "colourLoc");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

}
