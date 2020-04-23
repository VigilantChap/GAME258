#include "StartScene.h"

StartScene::StartScene() : Scene() {

}

StartScene::~StartScene() {

}

bool StartScene::OnCreate() {
	Debug::Info("Creating Start Scene", "StartScene.cpp", __LINE__);
	CoreEngine::GetInstance()->SetSceneNum(1);
	return true;
}

void StartScene::Update(const float deltaTime_) {

}

void StartScene::Render() {

}