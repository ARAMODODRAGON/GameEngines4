#include "GUIObject.h"

GUIObject::GUIObject(const vec2& position_) : position(position_), tag("") { 

}

GUIObject::~GUIObject() {
	for (GUIComponent* c : components) {
		delete c;
	}
	components.clear();
}

void GUIObject::Draw(Camera* camera) {
	for (GUIComponent* c : components) {
		c->Draw(camera, position);
	}
}

bool GUIObject::ContainsPoint(const vec2& point) {
	for (GUIComponent* c : components) {
		if (c->FindContainingPoint(position, point))
			return true;
	}
	return false;
}