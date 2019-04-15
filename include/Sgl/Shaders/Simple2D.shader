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

uniform mat4 u_Proj;

void main() {
	gl_Position = u_Proj * vec4(position, 1.0);
	f_color = color;
	f_uv = uv;
	f_tid = tid;
}

#shader fragment
#version 330 core

uniform sampler2D f_Sampler[16];

out vec4 fragColor;
in vec4  f_color;
in vec2  f_uv;
in float f_tid;

// Temporary solution for indexing the sampler array
vec4 GetValueFromSamplerArray(float ndx, vec2 uv) {
	if (ndx < .5) { return texture(f_Sampler[0], uv); }
	else if (ndx < 1.5)  { return texture(f_Sampler[1],  uv); }
	else if (ndx < 2.5)  { return texture(f_Sampler[2],  uv); }
	else if (ndx < 3.5)  { return texture(f_Sampler[3],  uv); }
	else if (ndx < 4.5)  { return texture(f_Sampler[4],  uv); }
	else if (ndx < 5.5)  { return texture(f_Sampler[5],  uv); }
	else if (ndx < 6.5)  { return texture(f_Sampler[6],  uv); }
	else if (ndx < 7.5)  { return texture(f_Sampler[7],  uv); }
	else if (ndx < 8.5)  { return texture(f_Sampler[8],  uv); }
	else if (ndx < 9.5)  { return texture(f_Sampler[9],  uv); }
	else if (ndx < 10.5) { return texture(f_Sampler[10], uv); }
	else if (ndx < 11.5) { return texture(f_Sampler[11], uv); }
	else if (ndx < 12.5) { return texture(f_Sampler[12], uv); }
	else if (ndx < 13.5) { return texture(f_Sampler[13], uv); }
	else if (ndx < 14.5) { return texture(f_Sampler[14], uv); }
	else if (ndx < 15.5) { return texture(f_Sampler[15], uv); }
}

void main() {
	fragColor = GetValueFromSamplerArray(f_tid, f_uv);
}

)"
