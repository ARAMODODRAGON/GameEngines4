#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
using namespace glm;
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>

class Camera { 

	/// variables
	glm::vec3 position;
	glm::mat4 persp, ortho;
	float fieldofview;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldup;

	std::vector<LightSource*> lights;

	void UpdateCameraVec();

public:
	Camera();
	~Camera();

	void OnDestroy();

	/// adding light sources
	void AddLightSource(LightSource* light);

	/// getters
	glm::mat4 GetView() const;
	glm::mat4 GetPersp() const;
	glm::mat4 GetOrtho() const;
	vec2 GetClippingPlanes() const;
	vec3 GetPosition() const { return position; }
	std::vector<LightSource*> GetLightSourceList() const { return lights; }

	/// setters
	void SetPosition(glm::vec3 pos);
	void SetRotation(float yaw_, float pitch_);

	void ProcessMouseMovement(glm::vec2 offset);
	void ProcessMouseZoom(int y);

};


#endif // !CAMERA_H