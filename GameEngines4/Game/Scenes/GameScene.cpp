#include "GameScene.h"
#include "../../Engine/Core/Debug.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>
#include "../../Engine/GUI/GUIImageComponent.h"
#include "../../Engine/Audio/AudioHandler.h"
#include "../../Engine/Audio/AudioSource.h"
#include "../../Engine/Components/PlayOnHit.h"
#include "../../Engine/Particles/ParticleEmitter.h"

GameScene::GameScene() : IScene() { }

GameScene::~GameScene() {
	SceneGraph::GetSingleton()->OnDestroy();
}

bool GameScene::OnCreate() {
	DEBUG_INFO("Creating GameScene");

	CollisionHandler::GetSingleton()->OnCreate(100);

	CoreEngine::GetSingleton()->SetCamera(new Camera());
	CoreEngine::GetSingleton()->GetCamera()->SetPosition(glm::vec3(0.0f, 2.0f, 10.0f));

	AudioHandler::GetSingleton()->Initialize();


	// create shape gameobject

	GLuint colorShProg = ShaderHandler::GetSingleton()->GetShader("TextureShader");

	// create model
	Model* model0 = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", colorShProg);
	Model* model1 = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", colorShProg);

	SceneGraph::GetSingleton()->AddModel(model0);
	SceneGraph::GetSingleton()->AddModel(model1);

	// gameobject
	GameObject* apple = new GameObject(model1, glm::vec3(5.0f, -1.0f, 0.0f));
	apple->SetScale(glm::vec3(0.5f));

	apple->AddComponent<AudioSource>(string("Resources/Sounds/ZAP_Sound.wav") /* via freesound */);
	apple->AddComponent<PlayOnHit>(); // needs to be added after so it can get a ptr to the audio source
	apple->AddComponent<ParticleEmitter>(1000, "ParticleShader");

	SceneGraph::GetSingleton()->AddGameObject(new GameObject(model0));
	SceneGraph::GetSingleton()->AddGameObject(apple, "apple");

	// add a light
	CoreEngine::GetSingleton()->GetCamera()->AddLightSource(new LightSource(vec3(1.0f, 4.0f, 5.0f), 0.1f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));

	std::cout << "dice  min: " << glm::to_string(model0->GetBoundingBox().min) << std::endl;
	std::cout << "dice  max: " << glm::to_string(model0->GetBoundingBox().max) << std::endl;
	std::cout << "apple min: " << glm::to_string(model1->GetBoundingBox().min) << std::endl;
	std::cout << "apple max: " << glm::to_string(model1->GetBoundingBox().max) << std::endl;

	GUIObject* gui = new GUIObject(vec2(0.0f));
	GUIImageComponent* igui = gui->AddComponent<GUIImageComponent>();
	if (igui) {
		TextureHandler::GetSingleton()->CreateTexture("test", "Resources/Textures/CheckerboardTexture.png");
		igui->OnCreate("test", CoreEngine::GetSingleton()->GetScreenSize() * 0.2f, vec2(0.1f, 0.1f));
	}
	SceneGraph::GetSingleton()->AddGUIObject(gui, "test GUI");


	return true;
}

void GameScene::Update(const float& delta) {
	SceneGraph::GetSingleton()->Update(delta);
	AudioHandler::GetSingleton()->Update();
}

void GameScene::Render() {
	SceneGraph::GetSingleton()->Render(CoreEngine::GetSingleton()->GetCamera());
}

void GameScene::Draw() {
	SceneGraph::GetSingleton()->Draw(CoreEngine::GetSingleton()->GetCamera());
}

void GameScene::OnDestroy() {
	CollisionHandler::GetSingleton()->OnDestroy();
	AudioHandler::GetSingleton()->OnDestroy();
}




