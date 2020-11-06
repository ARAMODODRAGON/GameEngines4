#include "Game1.h"
#include "../Engine/Core/CoreEngine.h"
#include "../Engine/Core/Debug.h"
#include "../Engine/Graphics/ShaderHandler.h"

bool Game1::OnCreate() {
	if (CoreEngine::GetSingleton()->GetCurrentScene() == 0) {
		scene = new StartScene();
		currentSceneNumber = 0;
		return scene->OnCreate();
	}

	ShaderHandler::GetSingleton()->CreateProgram("ColorShader", "Engine/Shaders/ColorShader.vert", "Engine/Shaders/ColorShader.frag");
	ShaderHandler::GetSingleton()->CreateProgram("TextureShader", "Engine/Shaders/TextureShader.vert", "Engine/Shaders/TextureShader.frag");
	ShaderHandler::GetSingleton()->CreateProgram("SpriteShader", "Engine/Shaders/SpriteVertShader.glsl", "Engine/Shaders/SpriteFragShader.glsl");
	ShaderHandler::GetSingleton()->CreateProgram("ParticleShader", "Engine/Shaders/ParticleShader.vert", "Engine/Shaders/ParticleShader.frag");

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

	// swap buffers
	SDL_GL_SwapWindow(CoreEngine::GetSingleton()->GetWindow()->GetWindow());

}

void Game1::Draw() {
	if (scene) scene->Draw();
}

void Game1::OnDestroy() {

}
