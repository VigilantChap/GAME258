#include "Game1.h"
#include "Scenes/GameScene.h"
#include "Scenes/StartScene.h"

Game1::Game1() : GameInterface(), currentScene(nullptr),  currentSceneNum(0) {

}

Game1::~Game1() {
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate() {
	if (CoreEngine::GetInstance()->GetSceneNum() == 0) {
		currentScene = new StartScene();
		if (!currentScene->OnCreate()) {
			Debug::FatalError("Scene failed to be created", "Game1.cpp", __LINE__);
			return false;
		}
		return true;
	}

	Debug::FatalError("Engine scene number is not zero", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_) {
	if (currentSceneNum != CoreEngine::GetInstance()->GetSceneNum()) BuildScene();

	currentScene->Update(deltaTime_);
}

void Game1::Render() {
	currentScene->Render();
}

void Game1::BuildScene() {
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetSceneNum())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	if (!currentScene->OnCreate()) {
		Debug::FatalError("Failed to create scene", "Game1.cpp", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}

	currentSceneNum = CoreEngine::GetInstance()->GetSceneNum();
}