R"(
#shader vertex
#version 300 es

in vec3 position;
in vec4 color;
in vec2 uv;
in float tid;

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
#version 300 es

precision mediump float;

const int MAX_TEXTURES = 16;

uniform sampler2D u_Sampler[MAX_TEXTURES];

in vec4  f_color;
in vec2  f_uv;
in float f_tid;
out vec4 fragColor;

void main() {
	int tid = int(f_tid);
	for (int i = 0; i < MAX_TEXTURES; i++) {
		if (tid == i)
			fragColor = texture(u_Sampler[i], f_uv);
	}
}
)"