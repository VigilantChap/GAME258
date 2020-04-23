#include "GameScene.h"

GameScene::GameScene() : Scene(){

}

GameScene::~GameScene() {
}

bool GameScene::OnCreate() {
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(
		new LightSource(glm::vec3(0.0f, 0.0f, 2.0f),
			0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));


	Model* model1 = new Model("./Resources/Models/Dice.obj", 
		"./Resources/Materials/Dice.mtl", 
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model1);


	Model* model2 = new Model("./Resources/Models/Apple.obj", 
		"./Resources/Materials/Apple.mtl", 
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model2);

	
	SceneGraph::GetInstance()->AddGameObject(new GameObject(model1));
	
	GameObject* apple = new GameObject(model2, glm::vec3(2.0f, -1.0f, 0.0f));
	apple->SetScale(glm::vec3(0.5f));
	SceneGraph::GetInstance()->AddGameObject(apple, "apple");

	return true;
}

void GameScene::Update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render() {
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}