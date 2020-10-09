#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H
#include <glm/glm.hpp>
using glm::vec2;
#include "../Camera/Camera.h"

class GUIComponent {

public:

	GUIComponent() { }
	virtual ~GUIComponent() = 0 { }

	// inherited functions
	virtual void Draw(Camera* camera, const vec2& position) = 0;
	virtual bool FindContainingPoint(const vec2& position, const vec2& point) = 0;

};

#endif // !GUI_COMPONENT_H