#include "Camera.h"
#include "../Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>

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

	std::cout << "ortho: " << glm::to_string(ortho) << std::endl;
	/*( 0.001563,  0.000000,  0.000000, 0.000000),
	  ( 0.000000,  0.002778,  0.000000, 0.000000),
	  ( 0.000000,  0.000000, -1.000000, 0.000000),
	  (-1.000000, -1.000000, -0.000000, 1.000000)*/
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

vec2 Camera::GetClippingPlanes() const {
	return vec2(nearPlane, farPlane);
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

void Camera::ProcessMouseMovement(glm::vec2 offset) {
	offset *= 0.05f;

	yaw += offset.x;
	pitch += offset.y;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	while (yaw > 360.0f) yaw -= 360.0f;
	while (yaw < 0.0f) yaw += 360.0f;

	UpdateCameraVec();
}

void Camera::ProcessMouseZoom(int y) {
	if (y != 0) position += static_cast<float>(y) * (forward * 2.0f);
}
