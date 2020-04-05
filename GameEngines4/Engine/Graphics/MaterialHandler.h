#ifndef MATERIAL_HANDLER_H
#define MATERIAL_HANDLER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

struct Material {

	Material()
		: name("")
		, diffuseMap(0)
		, shinyness(0.0f)
		, transparency(0.0f)
		, ambient(1.0f)
		, diffuse(1.0f)
		, specular(0.0f) { }

	std::string name;

	GLuint diffuseMap; // newmtl

	float shinyness; // Ns
	float transparency; // d

	glm::vec3 ambient; //Ka
	glm::vec3 diffuse; //Kd
	glm::vec3 specular; //Ks

};

class MaterialHandler {

	static std::unique_ptr<MaterialHandler> singleton;
	friend std::default_delete<MaterialHandler>;

	// disable copy & move constructors/operators
	MaterialHandler(const MaterialHandler&) = delete;
	MaterialHandler(MaterialHandler&&) = delete;
	MaterialHandler& operator=(const MaterialHandler&) = delete;
	MaterialHandler& operator=(MaterialHandler&&) = delete;

	MaterialHandler();
	~MaterialHandler();

	static std::vector<Material> materials;

public:

	static MaterialHandler* GetSingleton() {
		// check if instance exists and set it if it does not
		if (singleton.get() == nullptr)
			singleton.reset(new MaterialHandler());
		// return singleton
		return singleton.get();
	}

	void AddMaterial(Material mat_);
	const Material GetMaterial(const std::string& name_);
	void OnDestroy();

};

#endif // !MATERIAL_HANDLER_H