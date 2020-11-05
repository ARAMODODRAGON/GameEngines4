#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;
layout (location = 4) in float size;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 outNormal;
out vec2 outTexCoords;
out vec3 outColor;

void main() {

	vec4 cameraVector =  view * model * vec4(position,1)

	float distance = sqrt(cameraVector.xyz * cameraVector.xyz);  // length of the camera vector 
	
	float attenuation = inversesqrt(0.1f * distance);

	gl_PointSize = 
	
	//gl_Position = projection * view * model * vec4(vertex, 1.0f);
	//outNormal = normal;
	//outTexCoords = texCoords;
	//outColor = color;
}