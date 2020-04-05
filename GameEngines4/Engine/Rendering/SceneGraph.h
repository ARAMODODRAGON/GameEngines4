#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include <memory>
#include <map>
#include <vector>
#include "3D/GameObject.h"
#include "../Math/CollisionHandler.h"

class SceneGraph {

	static std::unique_ptr<SceneGraph> Singleton;
	friend std::default_delete<SceneGraph>;

	// disable copy & move constructors/operators for singleton
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	SceneGraph();
	~SceneGraph();

	static std::map<GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;

public:

	static SceneGraph* GetSingleton() {
		// check if instance exists
		if (Singleton.get() == nullptr) {
			Singleton.reset(new SceneGraph());
		}

		// return singleton
		return Singleton.get();
	}

	void OnDestroy();

	void AddModel(Model* model_);
	void AddGameObject(GameObject* go_, std::string name_ = "");
	GameObject* GetGameObject(std::string name_);

	void Update(const float delta);
	void Render(Camera* camera_);

};

#endif // !SCENE_GRAPH_H