#version 450 core

uniform vec3 position;
uniform float size;

uniform mat4 view;
uniform mat4 proj;

void main() {

	vec4 tmpPos = view * vec4(position, 1.0f);

	gl_PointSize = size * inversesqrt(0.1 * length(tmpPos.xyz));
	gl_Position = proj * tmpPos;
}