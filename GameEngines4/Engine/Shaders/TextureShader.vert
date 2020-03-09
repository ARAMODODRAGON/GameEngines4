#version 450 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 outNormal;
out vec2 outTexCoords;
out vec3 outColor;
out vec3 outFragPos;

void main() {

	gl_Position = projection * view * model * vec4(vertex, 1.0f);
    outNormal = (transpose(inverse(model)) * vec4(normal, 1.0f)).xyz;
    outTexCoords = texCoords;
    outColor = color;
    outFragPos = (model * vec4(vertex,1.0f)).xyz;


}