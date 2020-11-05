#version 450 core
in vec2 TexCoords;

out vec4 colour;

uniform vec4 colours;
layout (location = 0)
uniform sampler2D inputTexture;

void main() {
	vec4 tmpColour = texture(inputTexture, TexCoords) * colours;
	colour = tmpColour;
}