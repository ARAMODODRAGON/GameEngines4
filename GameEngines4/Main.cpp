#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) {
	
	// set game
	CoreEngine::GetSingleton()->SetIGame(new Game1());

	// create engine
	if (!CoreEngine::GetSingleton()->OnCreate("title", 1280, 720)) {
		return 1;
	}

	// start main loop
	CoreEngine::GetSingleton()->Run();
	
	CoreEngine::GetSingleton()->OnDestroy();

	return 0;
}