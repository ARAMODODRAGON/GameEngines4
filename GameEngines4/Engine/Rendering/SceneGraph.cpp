#include "SceneGraph.h"
#include "../Graphics/ShaderHandler.h"

std::unique_ptr<SceneGraph> SceneGraph::Singleton = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels;
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects;
std::map<std::string, GUIObject*> SceneGraph::sceneGUIObjects;

SceneGraph::SceneGraph() : guiShaderProgram(0) {
	guiShaderProgram = ShaderHandler::GetSingleton()->GetShader("SpriteShader");
}

SceneGraph::~SceneGraph() {

}

void SceneGraph::Draw(Camera* camera) {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(guiShaderProgram);

	for (const auto& p : sceneGUIObjects) {
		p.second->Draw(camera);
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void SceneGraph::OnDestroy() {

	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects)
			delete go.second;
		sceneGameObjects.clear();
	}

	if (sceneGUIObjects.size() > 0) {
		for (auto go : sceneGUIObjects)
			delete go.second;
		sceneGUIObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto mv : sceneModels) {
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

void SceneGraph::AddGUIObject(GUIObject* gui, std::string tag) {
	if (tag == "") {
		std::string newTag = "GUIObject " + std::to_string(sceneGUIObjects.size() + 1);
		gui->SetTag(newTag);
		sceneGUIObjects[newTag] = gui;
	} else if (sceneGUIObjects.find(tag) == sceneGUIObjects.end()) {
		gui->SetTag(tag);
		sceneGUIObjects[tag] = gui;
	} else {
		std::string newTag = "GUIObject " + std::to_string(sceneGUIObjects.size() + 1);
		gui->SetTag(newTag);
		sceneGUIObjects[newTag] = gui;

		DEBUG_ERROR("Cannot add GUIObject with name " + tag + " (name already exists) given new name: " + newTag);
	}
}

GUIObject* SceneGraph::GetGUIObject(std::string tag) {
	if (sceneGUIObjects.find(tag) != sceneGUIObjects.end())
		return sceneGUIObjects[tag];
	return nullptr;
}

void SceneGraph::Update(const float delta) {
	for (std::pair<const std::string, GameObject*> go : sceneGameObjects) {
		go.second->Update(delta);
	}
}

void SceneGraph::Render(Camera* camera_) {
	// render models
	for (std::pair<const GLuint, std::vector<Model*>> mo : sceneModels) {
		glUseProgram(mo.first);
		for (Model* model : mo.second) {
			model->Render(camera_);
		}
	}
	glUseProgram(0);

	// render game objects (the components essentially)
	for (auto gpair : sceneGameObjects) {
		gpair.second->Render(camera_);
	}
}
