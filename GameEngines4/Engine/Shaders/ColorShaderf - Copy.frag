#version 450 core
out vec4 fragColor;

in vec3 outNormal;
in vec2 outTexCoords;
in vec3 outColor;


void main() {
	

	fragColor = vec4(outColor, 0.1);

}