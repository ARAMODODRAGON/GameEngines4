#ifndef SCENE_STARTSCENE_H
#define SCENE_STARTSCENE_H

#include "../../Engine/Core/IScene.h"

class StartScene : public IScene {
public:

	// cosntructor and destructor
	StartScene() : IScene() { }
	virtual ~StartScene() { }

	// inherited via IScene
	virtual bool OnCreate() override;

	virtual void Update(const float& delta) override;

	virtual void Render() override;

	virtual void OnDestroy() override;

private:

};


#endif // !SCENE_STARTSCENE_H
