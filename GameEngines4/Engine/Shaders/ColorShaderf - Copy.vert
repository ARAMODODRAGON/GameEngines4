#version 450 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

uniform mat4 modelMat;

out vec3 outNormal;
out vec2 outTexCoords;
out vec3 outColor;

void main() {
	
	gl_Position = modelMat * vec4(vertex, 0.1f);
	outNormal = normal;
	outTexCoords = texCoords;
	outColor = color;
}