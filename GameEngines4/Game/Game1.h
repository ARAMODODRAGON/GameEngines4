#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/IGame.h"
#include "../Engine/Core/IScene.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

	class Game1 : public IGame {
	private:

		// scene
		IScene* scene;
		int currentSceneNumber;

	public:
		// constructor and destructor
		Game1() : IGame(), scene(nullptr), currentSceneNumber(0) { }
		virtual ~Game1() { }

		// inherited via IGame
		virtual bool OnCreate() override;
		virtual void Update(const float& delta) override;
		virtual void Render() override;
		virtual void OnDestroy() override;

		// methods
		void BuildScene();
	};



#endif // !GAME1_H