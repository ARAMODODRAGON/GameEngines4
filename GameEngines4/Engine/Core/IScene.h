#ifndef ISCENE_H
#define ISCENE_H

#include "../Rendering/3D/GameObject.h"
#include "../../Engine/Rendering/3D/Mesh.h"
#include "../../Engine/Rendering/3D/Model.h"

class IScene {
public:
	IScene() { }
	virtual ~IScene() { }

	virtual bool OnCreate() = 0;
	virtual void Update(const float& delta) = 0;
	virtual void Render() = 0;
	virtual void Draw() = 0;
	virtual void OnDestroy() = 0;

};

#endif // !ISCENE_H