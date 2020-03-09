#include "GameScene.h"
#include "../../Engine/Core/Debug.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Core/CoreEngine.h"

bool GameScene::OnCreate() {
	DEBUG_INFO("Creating GameScene");

	CoreEngine::GetSingleton()->SetCamera(new Camera());
	CoreEngine::GetSingleton()->GetCamera()->SetPosition(glm::vec3(0.0f, 2.0f, 10.0f));

	// create shape gameobject

	GLuint colorShProg = ShaderHandler::GetSingleton()->GetShader("TextureShader");
	
	// create model
	Model* model = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", colorShProg);

	// gameobject
	shape = new GameObject(model);

	// add a light
	CoreEngine::GetSingleton()->GetCamera()->AddLightSource(new LightSource(vec3(1.0f, 4.0f, 5.0f), 0.1f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));

	return true;
}

void GameScene::Update(const float& delta) { 
	shape->Update(delta);
}

void GameScene::Render() { 
	shape->Render(CoreEngine::GetSingleton()->GetCamera());
}

void GameScene::OnDestroy() { 
	delete shape; shape = nullptr;
}
