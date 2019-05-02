R"(
#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in float tid;

out DATA
{
	vec3 position;
	vec2 uv;
	float tid;
	// vec2 mask_uv; TODO
	// float mid; TODO
	vec4 color;
} vs_out;

uniform mat4 u_Projection;

void main() {
	gl_Position = u_Projection * vec4(position, 1.0);
	vs_out.position = position;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
}

#shader fragment
#version 330 core

const int MAX_TEXTURES = 16; // Max ??

uniform sampler2D u_Sampler[MAX_TEXTURES];

in DATA
{
	vec3 position;
	vec2 uv;
	float tid;
	// vec2 mask_uv; TODO
	// float mid; TODO
	vec4 color;
} fs_in;

layout (location = 0) out vec4 color;

void main() {
    vec4 texColor = fs_in.color;

    // Has a texture
    if(fs_in.tid > 0) {
        int tid = int(fs_in.tid - 0.5);
        texColor = fs_in.color * texture(u_Sampler[tid], fs_in.uv);
    }
	color = texColor;
}

)"
