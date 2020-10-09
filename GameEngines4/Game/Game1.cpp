#include "Game1.h"
#include "../Engine/Core/CoreEngine.h"
#include "../Engine/Core/Debug.h"

bool Game1::OnCreate() {
	if (CoreEngine::GetSingleton()->GetCurrentScene() == 0) {
		scene = new StartScene();
		currentSceneNumber = 0;
		return scene->OnCreate();
	}

	Debug::FatalError("SceneNumber was not initialized to 0", "Game1.cpp", __LINE__);
	return false;
}

void Game1::BuildScene() {
	// delete old scene
	delete scene; scene = nullptr;

	// create the specific scene
	switch (CoreEngine::GetSingleton()->GetCurrentScene()) {
		case 0:
			scene = new StartScene();
			break;
		case 1:
			scene = new GameScene();
			break;
		default: break;
	}

	// set current scene number
	currentSceneNumber = CoreEngine::GetSingleton()->GetCurrentScene();

	// call oncreate
	if (!scene->OnCreate()) {
		CoreEngine::GetSingleton()->Exit();
	}

}

void Game1::Update(const float& delta) {
	if (currentSceneNumber != CoreEngine::GetSingleton()->GetCurrentScene()) {
		BuildScene();
	}
	if (scene) scene->Update(delta);
}

void Game1::Render() {
	if (scene) scene->Render();
}

void Game1::Draw() {
	if (scene) scene->Draw();
}

void Game1::OnDestroy() {

}
