#include "Camera.h"
#include "../Core/CoreEngine.h"

void Camera::UpdateCameraVec() {
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);
	
	right = glm::normalize(glm::cross(forward, worldup));

	up = glm::normalize(glm::cross(right, forward));

}

Camera::Camera()
	: position(glm::vec3(0.0f, 0.0f, 0.0f))
	, fieldofview(45.0f)
	, forward(glm::vec3(0.0f, 0.0f, -1.0f))
	, up(glm::vec3(0.0f, 1.0f, 0.0f))
	, worldup(glm::vec3(0.0f, 1.0f, 0.0f))
	, nearPlane(2.0f)
	, farPlane(100.0f)
	, pitch(0.0f)
	, yaw(-90.0f) {

	// create matricies
	persp = glm::perspective(
		fieldofview,
		CoreEngine::GetSingleton()->GetScreenSize().x / CoreEngine::GetSingleton()->GetScreenSize().y,
		nearPlane,
		farPlane
	);
	ortho = glm::ortho(
		0.0f,
		CoreEngine::GetSingleton()->GetScreenSize().x,
		0.0f,
		CoreEngine::GetSingleton()->GetScreenSize().y,
		-1.0f,
		1.0f
	);
}

Camera::~Camera() { OnDestroy(); }

void Camera::OnDestroy() { 
	// delete all of the light sources
	for (LightSource* light : lights)
		delete light;
	lights.clear();
}

void Camera::AddLightSource(LightSource* light) { 
	lights.push_back(light);
}

glm::mat4 Camera::GetView() const {
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPersp() const {
	return persp;
}

glm::mat4 Camera::GetOrtho() const {
	return ortho;
}

void Camera::SetPosition(glm::vec3 pos) {
	position = pos;

	UpdateCameraVec();
}

void Camera::SetRotation(float yaw_, float pitch_) {
	yaw = yaw_;
	pitch = pitch_;

	UpdateCameraVec();
}
