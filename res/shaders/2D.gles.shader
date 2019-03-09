#shader vertex
#version 100

attribute vec3 position;
attribute vec4 color;

varying vec4 f_color;

uniform mat4 u_Proj;

void main() {

	gl_Position = u_Proj * vec4(position, 1.0);
    f_color = color;
}

#shader fragment
#version 100
precision mediump float;

varying vec4 f_color;

void main() {
	gl_FragColor = f_color;
}