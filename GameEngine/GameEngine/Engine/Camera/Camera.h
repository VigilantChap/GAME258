#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();

	void OnDestroy();

	inline void SetPosition(glm::vec3 position_) { position = position_; }
	inline void SetRotation(float yaw_, float pitch_) { yaw = yaw_; pitch = pitch_; }

	inline glm::mat4 GetView() const { return glm::lookAt(position, position + forward, up); }
	inline glm::mat4 GetPerspective() const { return perspective; }
	inline glm::mat4 GetOrtho() const { return orthographic; }
	//inline glm::mat4 GetView() const { return glm::lookAt(position, position + forward, up); }
	//inline glm::mat4 GetPerspective() const { return perspective; }
	//inline glm::mat4 GetOrthographic() const { return orthographic; }
	inline glm::vec3 GetPosition() const { return position; }

	void AddLightSource(LightSource* newLight_);
	std::vector<LightSource*> GetLightSources();

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseScroll(int y_);

private:
	void UpdateCameraVectors();

	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;

	std::vector<LightSource*> lightSources;

};


#endif // !CAMERA_H