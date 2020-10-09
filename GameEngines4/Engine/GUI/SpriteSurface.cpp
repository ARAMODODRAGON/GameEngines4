#include "SpriteSurface.h"
#include "../Graphics/ShaderHandler.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SpriteSurface::SpriteSurface(const string& texture_, const vec2& scale_, const float& angle_, const vec4& tint_)
	: VAO(0), VBO(0)
	, modelLoc(0), projLoc(0), tintLoc(0), textureLoc(0)
	, texID(0)
	, scale(scale_), angle(angle_), tint(tint_), sizeX(0), sizeY(0) {

	texID = TextureHandler::GetSingleton()->GetTexture(texture_);
	if (texID == 0) {
		DEBUG_ERROR("Could not load texture");
	}

	const auto* tdata = TextureHandler::GetSingleton()->GetTextureStruct(texture_);
	if (tdata) {
		sizeX = tdata->width;
		sizeY = tdata->height;
		DEBUG_INFO("Width: " + std::to_string(sizeX) + " Height: " + std::to_string(sizeY));
	} else {
		DEBUG_ERROR("No texture data!");
	}

	struct SpriteVert {
		vec2 position;
		vec2 uv;
	};
	SpriteVert verticies[] = {
		{ vec2(-0.5f, 0.5f), vec2(0.0f, 0.0f) },
		{ vec2(0.5f, 0.5f), vec2(1.0f, 0.0f) },
		{ vec2(-0.5f, -0.5f), vec2(0.0f, 1.0f) },
		{ vec2(0.5f, -0.5f), vec2(1.0f, 1.0f) }
	};

	// create vao and vbo
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(SpriteVert), verticies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVert), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVert), (GLvoid*)offsetof(SpriteVert, uv));

	// load shader
	unsigned int shaderProgram = ShaderHandler::GetSingleton()->GetShader("SpriteShader");
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	tintLoc = glGetUniformLocation(shaderProgram, "tintColour");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	DEBUG_INFO("shaderProgram: " + std::to_string(shaderProgram));
	DEBUG_INFO("modeLoc: " + std::to_string(modelLoc));
	DEBUG_INFO("projLoc: " + std::to_string(projLoc));
	DEBUG_INFO("tintLoc: " + std::to_string(tintLoc));
	DEBUG_INFO("textureLoc: " + std::to_string(textureLoc));

}

SpriteSurface::~SpriteSurface() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void SpriteSurface::Draw(Camera* camera, const vec2& position) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	glm::mat4 model;
	glm::translate(model, vec3(position, 0.0f));
	glm::rotate(model, angle, vec3(0.0f, 0.0f, 1.0));
	//glm::scale(model, vec3(scale.x * sizeX, scale.y * sizeY, 1.0f));
	glm::scale(model, vec3(scale.x, scale.y, 1.0f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glm::mat4 ortho = camera->GetOrtho();
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));

	glUniform4f(tintLoc, tint.r, tint.g, tint.b, tint.a);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}