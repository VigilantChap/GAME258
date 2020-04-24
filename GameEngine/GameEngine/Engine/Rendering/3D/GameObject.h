#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	void Render(Camera* camera_);
	void Update(const float deltaTime_);

	inline glm::vec3 GetPosition() const { return position; }
	inline float getAngle() const { return angle; }
	inline glm::vec3 GetRotation() const { return rotation; }
	inline glm::vec3 GetScale() const { return scale; }
	
	inline std::string GetTag() const { return tag; }


	void SetPosition(glm::vec3 position_);

	void SetAngle(float angle_);

	void SetRotation(glm::vec3 rotation_);

	void SetScale(glm::vec3 scale_);

	inline void SetTag(std::string tag_) { tag = tag_; }

	inline BoundingBox GetBoundingBox() const { return box; }

	inline bool GetHit() const { return hit; }
	inline void SetHit(bool hit_, int buttonType_) { hit = hit_; if (hit) std::cout << tag + " was hit" << std::endl; }

private:
	Model* model;
	int modelInstance;

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	BoundingBox box;
	std::string tag;

	bool hit;
};


#endif // !GAMEOBJECT_H