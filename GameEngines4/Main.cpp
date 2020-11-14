#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"
#include <nlohmann\json.hpp>
#include <fstream>
using nlohmann::json;

int main(int argc, char* argv[]) {

	json j = nullptr;
	std::fstream stream("Config.json");
	if (stream.is_open()) {
		stream >> j;
		stream.close();
	}

	// set game
	CoreEngine::GetSingleton()->SetIGame(new Game1(), RendererType::OpenGL);

	// create engine
	std::string title = j["title"];
	uvec2 size;
	size.x = j["size"]["width"];
	size.y = j["size"]["height"];

	if (!CoreEngine::GetSingleton()->OnCreate(title, size.x, size.y)) {
		return 1;
	}

	// start main loop
	CoreEngine::GetSingleton()->Run();

	CoreEngine::GetSingleton()->OnDestroy();

	return 0;
}