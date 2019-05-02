R"(
#shader vertex
#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in float tid;

vec3 f_position;
vec2 f_uv;
float f_tid;
// vec2 f_mask_uv; TODO
// float f_mid; TODO
vec4 f_color;

uniform mat4 u_Projection;

void main() {
	gl_Position = u_Projection * vec4(position, 1.0);
	f_position = position;
	f_uv = uv;
	f_tid = tid;
	f_color = color;
}

#shader fragment
#version 300 es

precision mediump float;

const int MAX_TEXTURES = 16;

uniform sampler2D u_Sampler[MAX_TEXTURES];

vec3 f_position;
vec2 f_uv;
float f_tid;
// vec2 f_mask_uv; TODO
// float f_mid; TODO
vec4 f_color;

layout (location = 0) out vec4 color;

void main() {
    vec4 texColor = f_color;

    // Has a texture
    if(f_tid > 0.0) {

        int tid = int(f_tid);
	    for (int i = 0; i < MAX_TEXTURES; i++) {
		    if (tid == i)
			    texColor = texture(u_Sampler[i], f_uv);
	    }
    }
	color = texColor;
}

)"
