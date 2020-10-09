#include "StartScene.h"
#include "../../Engine/Core/Debug.h"
#include "../../Engine/Core/CoreEngine.h"

bool StartScene::OnCreate() {
	Debug::Info("Creating StartScene", "StartScene.cpp", __LINE__);
	CoreEngine::GetSingleton()->SetCurrentScene(1);
	return true;
}

void StartScene::Update(const float& delta) { }

void StartScene::Render() { }

void StartScene::Draw() { }

void StartScene::OnDestroy() { }
