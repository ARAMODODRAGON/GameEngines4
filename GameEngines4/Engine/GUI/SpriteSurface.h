#ifndef SPRITE_SURFACE_H
#define SPRITE_SURFACE_H
#include <string>
using std::string;
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec4;
using glm::ivec2;
#include "../Graphics/TextureHandler.h"
#include "../Camera/Camera.h"

class SpriteSurface {

	unsigned int VAO, VBO;
	unsigned int modelLoc, projLoc, tintLoc, textureLoc;

	unsigned int texID;

	vec2 scale;
	float angle;
	vec4 tint;
	ivec2 size;
	
public:

	SpriteSurface(const string& texture_, const vec2& scale_, const float& angle_, const vec4& tint_);
	~SpriteSurface();

	// events
	void Draw(Camera* camera, const vec2& position);

	// getters & setters
	vec2 GetScale() const { return scale; }
	vec2 GetSize() const { return size; }
	vec2 GetScaledSize() const { return scale * vec2(size); }

};

#endif // !SPRITE_SURFACE_H