#ifndef SCENE_GAMESCENE_H
#define SCENE_GAMESCENE_H

#include "../../Engine/Core/IScene.h"

class GameScene : public IScene {
private:

	GameObject* shape;

public:

	// cosntructor and destructor
	GameScene() : IScene(), shape(nullptr) { }
	virtual ~GameScene() { }

	// inherited via IScene
	virtual bool OnCreate() override;

	virtual void Update(const float& delta) override;

	virtual void Render() override;

	virtual void OnDestroy() override;

private:

};


#endif // !SCENE_GAMESCENE_H
