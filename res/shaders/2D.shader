#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in float tid;

out vec4  f_color;
out vec2  f_uv;
out float f_tid;

uniform mat4 u_Proj;

void main() {

	gl_Position = u_Proj * vec4(position, 1.0);
    f_color = color;
}

#shader fragment
#version 330 core

uniform sampler2D f_Sampler;

out vec4 fragColor;

in vec4  f_color;
in vec2  f_uv;
in float f_tid;

void main() {
	fragColor = vec4(1.0);//texture(f_Sampler, f_uv);
}