#ifndef SCENE_GAMESCENE_H
#define SCENE_GAMESCENE_H

#include "../../Engine/Core/IScene.h"

class GameScene : public IScene {
private:

public:

	// cosntructor and destructor
	GameScene();
	virtual ~GameScene();

	// inherited via IScene
	virtual bool OnCreate() override;

	virtual void Update(const float& delta) override;

	virtual void Render() override;

	virtual void Draw() override;

	virtual void OnDestroy() override;

private:

};


#endif // !SCENE_GAMESCENE_H
