#include "MaterialHandler.h"

std::unique_ptr<MaterialHandler> MaterialHandler::singleton = nullptr;
std::vector<Material> MaterialHandler::materials = std::vector<Material>();

MaterialHandler::MaterialHandler() {
	materials.reserve(10);
}

MaterialHandler::~MaterialHandler() { }

void MaterialHandler::AddMaterial(Material mat_) {
	materials.push_back(mat_);
}

const Material MaterialHandler::GetMaterial(const std::string& name_) {
	for (Material& mat : materials) {
		if (mat.name == name_)
			return mat;
	}
	return Material();
}

void MaterialHandler::OnDestroy() {
	if (materials.size() > 0)
		materials.clear();
}


