#shader vertex
#version 100

attribute vec3 position;
attribute vec4 color;

varying vec4 color_frag;

uniform mat4 u_Proj;

void main() {

	gl_Position = u_Proj * vec4(position, 1.0);
    color_frag = color;
}

#shader fragment
#version 100
precision highp float;

varying vec4 color_frag;

void main() {
	gl_FragColor = color_frag;
}