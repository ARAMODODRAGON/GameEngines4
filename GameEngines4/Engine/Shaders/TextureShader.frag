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

uniform sampler2D image;
uniform vec3 cameraPos;
uniform Light light;

void main() {

	vec3 ambient = light.ambient* texture(image, outTexCoords).rgb* light.color;

    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(light.position - outFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * texture(image, outTexCoords).rgb* light.color;

    float specularStrength= 0.5;
    vec3 viewDir = normalize(cameraPos - outFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength* spec * light.color;

    vec3 result= ambient + diffuse + specular;

    fragColor = vec4(result, 1.0f);
    //fragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//fragColor = texture(image, outTexCoords);
}