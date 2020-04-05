#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::Singleton = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();

SceneGraph::SceneGraph() {

}

SceneGraph::~SceneGraph() {

}

void SceneGraph::OnDestroy() {

	if (sceneGameObjects.size() > 0) {
		for (std::pair<const std::string, GameObject*> go : sceneGameObjects)
			delete go.second;
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (std::pair<const GLuint, std::vector<Model*>> mv : sceneModels) {
			for (Model* model : mv.second) {
				delete model;
			}
			mv.second.clear();
		}
		sceneModels.clear();
	}

}

void SceneGraph::AddModel(Model* model_) {
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end()) {
		std::vector<Model*> tmp = std::vector<Model*>();
		tmp.reserve(10);
		tmp.push_back(model_);
		sceneModels.insert(std::pair < GLuint, std::vector<Model*>>(model_->GetShaderProgram(), tmp));
	} else {
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* go_, std::string name_) {
	if (name_ == "") {
		std::string newName = "GameObject " + std::to_string(sceneGameObjects.size() + 1);
		go_->SetName(newName);
		sceneGameObjects[newName] = go_;
	} else if (sceneGameObjects.find(name_) == sceneGameObjects.end()) {
		go_->SetName(name_);
		sceneGameObjects[name_] = go_;
	} else {
		std::string newName = "GameObject " + std::to_string(sceneGameObjects.size() + 1);
		go_->SetName(newName);
		sceneGameObjects[newName] = go_;

		DEBUG_ERROR("Cannot add gameobject with name " + name_ + " (name already exists) given new name: " + newName);
	}
	CollisionHandler::GetSingleton()->AddObject(go_);
}

GameObject* SceneGraph::GetGameObject(std::string name_) {
	if (sceneGameObjects.find(name_) != sceneGameObjects.end()) {
		return sceneGameObjects[name_];

	}
	return nullptr;
}

void SceneGraph::Update(const float delta) {
	for (std::pair<const std::string, GameObject*> go : sceneGameObjects) {
		go.second->Update(delta);
	}
}

void SceneGraph::Render(Camera* camera_) {
	for (std::pair<const GLuint, std::vector<Model*>> mo : sceneModels) {
		glUseProgram(mo.first);
		for (Model* model : mo.second) {
			model->Render(camera_);
		}
	}
	glUseProgram(0);
}
