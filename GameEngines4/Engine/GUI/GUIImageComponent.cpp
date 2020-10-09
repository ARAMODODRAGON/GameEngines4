#include "GUIImageComponent.h"

GUIImageComponent::GUIImageComponent()
	: sprSurface(nullptr), offset(0.0f) { }

GUIImageComponent::~GUIImageComponent() {
	if (sprSurface) delete sprSurface;
	sprSurface = nullptr;
}

void GUIImageComponent::OnCreate(
	const string& textureName_,
	const vec2& offset_,
	const vec2& scale_,
	const float& angle_,
	const vec4& tint_
) {
	offset = offset_;
	if (!sprSurface) {
		sprSurface = new SpriteSurface(textureName_, scale_, angle_, tint_);
	}


}

void GUIImageComponent::Draw(Camera* camera, const vec2& position) {
	sprSurface->Draw(camera, position + offset);
}

bool GUIImageComponent::FindContainingPoint(const vec2& position, const vec2& point) {
	if (!sprSurface) return false;

	vec2 min = position + offset - sprSurface->GetSize();
	vec2 max = position + offset + sprSurface->GetSize();

	if (point.x < min.x || point.x > max.x) return false;
	if (point.y < min.y || point.y > max.y) return false;
	return true;
}