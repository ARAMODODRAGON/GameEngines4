#ifndef COREENGINE_H
#define COREENGINE_H

#include <string>
#include <memory>
#include "Window.h"
#include "Timer.h"
#include "IGame.h"
#include "IScene.h"
#include "../Rendering/3D/GameObject.h"
#include "../Camera/Camera.h"
#include "../Graphics/TextureHandler.h"
#include "../Event/MouseEventListener.h"
#include "../Event/EventListener.h"
#include "../Rendering/SceneGraph.h"
#include "../Graphics/MaterialHandler.h"

class CoreEngine {
private:

	// singleton
	static std::unique_ptr<CoreEngine> Singleton;
	friend std::default_delete<CoreEngine>;

	// constructor and destructor
	CoreEngine() : isRunning(false), window(nullptr), fps(60), game(nullptr), currentSceneNumber(0),camera(nullptr) { }
	~CoreEngine() { OnDestroy(); }

public:

	// disable copy & move constructors/operators for singleton
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

private:

	// variables
	bool isRunning;
	Window* window;
	Timer timer;
	unsigned int fps;
	Camera* camera;

	// the game pointer
	IGame* game;

	// scene
	int currentSceneNumber;

public:

	// get singleton
	static CoreEngine* GetSingleton();

	// creation
	bool OnCreate(std::string name_, int width_, int height_);

	// the main loop
	void Run();

	// methods
	void Exit() { isRunning = false; }

	// getters
	bool GetIsRunning() const { return isRunning; }
	int GetCurrentScene() { return currentSceneNumber; }
	glm::vec2 GetScreenSize() { return glm::vec2(window->GetWidth(), window->GetHeight()); }
	Camera* GetCamera() { return camera; }

	// setters 
	void SetIGame(IGame* game_) { game = game_; }
	void SetCurrentScene(int sceneNumber);
	void SetCamera(Camera* camera_) { camera = camera_; }

	/// notify

	void NotifyOfMousePressed(glm::vec2 mousePos);
	void NotifyOfMouseReleased(glm::vec2 mousePos, int button);
	void NotifyOfMouseMove(glm::vec2 mousePos);
	void NotifyOfMouseScroll(int y);

private:

	// events
	void Update(const float& delta);
	void Render();
	void OnDestroy();

};

#endif // !COREENGINE_H