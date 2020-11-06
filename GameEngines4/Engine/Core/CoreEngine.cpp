#include "CoreEngine.h"
#include "Debug.h"
#include "../Graphics/ShaderHandler.h"
#include <glm/vec3.hpp>
#include "../Audio/AudioHandler.h"
#include "../Rendering/GL/GLRenderer.h"

std::unique_ptr<CoreEngine> CoreEngine::Singleton = nullptr;

CoreEngine* CoreEngine::GetSingleton() {
	// check if instance exists
	if (Singleton.get() == nullptr) {
		Singleton.reset(new CoreEngine());
	}

	// return singleton
	return Singleton.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_) {
	// initialize debug
	Debug::DebugInit();
	Debug::SetSeverity(Message_Type::Info);

	// create renderer
	switch (rendererType) {
		case RendererType::OpenGL: 
			renderer = new GLRenderer();
			break;
		default: DEBUG_FATALERROR("Renderer type not supported"); return false; 
	}

	// create window pointer
	window = new Window();

	// create window
	if (!window->OnCreate(name_, width_, height_, renderer)) {
		DEBUG_ERROR("Failed to create window");
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);

	//AudioHandler::GetSingleton()->Initialize();

	// create game
	if (game && !game->OnCreate()) {
		DEBUG_ERROR("Could not call game->OnCreate()");
	}

	// start timer
	timer.Start();

	return isRunning = true;
}

void CoreEngine::Run() {
	while (isRunning) {

		// update
		timer.UpdateGameTicks();

		EventListener::Update();

		Update(timer.GetDeltaTimer());

		// render
		Render();
		// wait for frame
		SDL_Delay(timer.GetSleepTime(fps));
	}


}

void CoreEngine::SetCurrentScene(int sceneNumber) {
	// set the current scene
	currentSceneNumber = sceneNumber;


}

void CoreEngine::NotifyOfMousePressed(glm::vec2 mousePos) { }

void CoreEngine::NotifyOfMouseReleased(glm::vec2 mousePos, int button) {
	CollisionHandler::GetSingleton()->MouseUpdate(mousePos, button);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mousePos) {
	if (camera) camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
}

void CoreEngine::NotifyOfMouseScroll(int y) {
	if (camera) camera->ProcessMouseZoom(y);
}

void CoreEngine::Update(const float& delta) {

	// update game
	if (game) {
		game->Update(delta);
	}

}

void CoreEngine::Render() {

	renderer->ClearScreen(vec4(0.0f, 0.0f, 0.0f, 1.0f));

	/// render objects
	if (game) {
		game->Render();

		game->Draw();
	}

}

void CoreEngine::OnDestroy() {

	//AudioHandler::GetSingleton()->OnDestroy();
	ShaderHandler::GetSingleton()->OnDestroy();
	TextureHandler::GetSingleton()->OnDestroy();
	SceneGraph::GetSingleton()->OnDestroy();
	MaterialHandler::GetSingleton()->OnDestroy();
	CollisionHandler::GetSingleton()->OnDestroy();

	// delete the game
	delete game; game = nullptr;
	// destroy the window pointer
	delete window; window = nullptr;
	// delete camera
	if (camera) delete camera;
	camera = nullptr;

	// exit sdl
	SDL_Quit();
	// quit program
	exit(0);
}
