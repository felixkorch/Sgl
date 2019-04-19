R"(
#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in float tid;

out vec4  f_color;
out vec2  f_uv;
out float f_tid;

uniform mat4 u_Projection;

void main() {
	gl_Position = u_Projection * vec4(position, 1.0);
	f_color = color;
	f_uv = uv;
	f_tid = tid;
}

#shader fragment
#version 330 core

const int MAX_TEXTURES = 16;

uniform sampler2D u_Sampler[MAX_TEXTURES];

out vec4 fragColor;
in vec4  f_color;
in vec2  f_uv;
in float f_tid;

void main() {
    int tid = int(f_tid + 0.5);
	fragColor = texture(u_Sampler[tid], f_uv);
}

)"
