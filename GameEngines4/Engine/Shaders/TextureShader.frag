#version 450 core
out vec4 fragColor;

in vec3 outNormal;
in vec2 outTexCoords;
in vec3 outColor;
in vec3 outFragPos;

struct Light {
	vec3 position;
	float ambient;
	float diffuse;
	vec3 color;
};

struct Material {
	sampler2D diffuseMap;
	float shinyness;
	float transparency;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 cameraPos;
uniform Light light;
uniform Material mat;

void main() {
	
	//ambient 
	vec3 ambient = light.ambient * mat.ambient * texture(mat.diffuseMap, outTexCoords).rgb * light.color;

	//diffuse
	vec3 norm = normalize(outNormal);
	vec3 lightDir = normalize(light.position - outFragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * mat.diffuse) * texture(mat.diffuseMap, outTexCoords).rgb* light.color;

	//specular
	vec3 viewDir = normalize(cameraPos - outFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shinyness);
	vec3 specular = (spec * mat.specular) * light.color;
	vec3 result= ambient + diffuse + specular;

	fragColor = vec4(result, mat.transparency);

}
