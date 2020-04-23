#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <map>
#include <vector>
#include "3D/GameObject.h"

class SceneGraph
{
public:
	//Disabling ability to duplicate a SceneGraph
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator =(const SceneGraph&) = delete;
	SceneGraph& operator =(SceneGraph&&) = delete;
	
	static SceneGraph* GetInstance();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* go_, std::string tag_ = "");
	GameObject* GetGameObject(std::string tag_);
	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void OnDestroy();

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	static std::map<GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;

};

#endif