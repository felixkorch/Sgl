#shader vertex
#version 100

attribute vec3 position;

void main() {

	gl_Position = vec4(position, 1.0);
}

#shader fragment
#version 100
precision mediump float;    
 
void main() {
	gl_FragColor = vec4(1.0);
}