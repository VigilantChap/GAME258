#include "Camera.h"
#include "../Core/CoreEngine.h"

Camera::Camera() : position(glm::vec3()), fieldOfView(45.0f), forward(glm::vec3(0.0f, 0.0f, 1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), worldUp(up),
nearPlane(2.0f), farPlane(50.0f), yaw(-90.0f), pitch(0.0f)
{
	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetWindowSize().x / CoreEngine::GetInstance()->GetWindowSize().y, nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x, 0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera() {
	OnDestroy();
}

void Camera::OnDestroy() {
	lightSources.clear();
}

void Camera::UpdateCameraVectors() {
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));
}

void Camera::AddLightSource(LightSource* newLight_) { lightSources.push_back(newLight_); }

std::vector<LightSource*> Camera::GetLightSources() { return lightSources; }


//mouse sensitivity
void Camera::ProcessMouseMovement(glm::vec2 offset_) {
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw < 0.0f) {
		yaw += 350.0f;
	}

	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}

	UpdateCameraVectors();

}

void Camera::ProcessMouseScroll(int y_) {
	if (y_ < 0 || y_ > 0) {
		position += static_cast<float>(y_)* (forward * 2.0f);
	}
	UpdateCameraVectors();
}