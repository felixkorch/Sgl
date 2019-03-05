#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 color_frag;

uniform mat4 u_Proj;

void main() {

	gl_Position = u_Proj * vec4(position, 1.0);
    color_frag = color;
}

#shader fragment
#version 330 core

out vec4 fragColor;
in vec4 color_frag;

void main() {
	fragColor = color_frag;
}