#include "Component.h"
#include "../../Core/Debug.h"

Component::Component() : object(nullptr) { }

Component::~Component() { }

void Component::SetObject(GameObject* object_) {
	if (object) {
		DEBUG_ERROR("Cant set object, it was already set!");
		return;
	}
	object = object_;
}

GameObject* Component::GetObject() const {
	return object;
}
