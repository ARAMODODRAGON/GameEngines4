#ifndef GUI_IMAGE_COMPONENT_H
#define GUI_IMAGE_COMPONENT_H
#include "GUIComponent.h"
#include "SpriteSurface.h"

class GUIImageComponent : public GUIComponent {

	SpriteSurface* sprSurface;
	vec2 offset;

public:

	GUIImageComponent();
	virtual ~GUIImageComponent() final;

	void OnCreate(
		const string& textureName,
		const vec2& offset = vec2(0.0f, 0.0f),
		const vec2& scale = vec2(1.0f, 1.0f),
		const float& angle = 0.0f,
		const vec4& tint = vec4(1.0f, 1.0f, 1.0f, 1.0f)
	);

	// inherited functions
	virtual void Draw(Camera* camera, const vec2& position) override;
	virtual bool FindContainingPoint(const vec2& position, const vec2& point) override;


};

#endif // !GUI_IMAGE_COMPONENT_H