#ifndef LIGHTSOURCE_H
#define LIGHTSOURCEH
#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 colour_);
	~LightSource();

	inline glm::vec3 GetPosition() { return position; }
	inline glm::vec3 GetColour() { return colour; }
	inline float GetAmbient() { return ambient; }
	inline float GetDiffuse() { return diffuse; }
	inline void SetPosition(glm::vec3 position_) { position = position_; }
	inline void SetColour(glm::vec3 colour_) { colour = colour_; }
	inline void SetAmbient(float ambient_) { ambient = ambient_; }
	inline void SetDiffuse(float diffuse_) { diffuse = diffuse_; }
private:
	glm::vec3 position;
	glm::vec3 colour;
	float ambient;
	float diffuse;

};
#endif