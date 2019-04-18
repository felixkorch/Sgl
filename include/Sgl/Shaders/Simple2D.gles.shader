R"(
#shader vertex
#version 100

attribute vec3 position;
attribute vec4 color;
attribute vec2 uv;
attribute float tid;

varying vec4  f_color;
varying vec2  f_uv;
varying float f_tid;

uniform mat4 u_Projection;

void main() {
	gl_Position = u_Projection * vec4(position, 1.0);
	f_color = color;
	f_uv = uv;
	f_tid = tid;
}

#shader fragment
#version 100

precision mediump float;

uniform sampler2D u_Sampler[16];

varying vec4  f_color;
varying vec2  f_uv;
varying float f_tid;

void main() {
	int tid = int(f_tid);
	for (int i = 0; i < 16; i++) {
		if (tid == i)
			gl_FragColor = texture2D(u_Sampler[i], f_uv);
	}
}
)"