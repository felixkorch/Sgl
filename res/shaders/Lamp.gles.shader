#shader vertex
#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_Proj;

void main() {

	gl_Position = u_Proj * vec4(position, 1.0);

}

#shader fragment
#version 300 es

precision highp float;

out vec4 fragColor;

void main() {

	fragColor = vec4(1.0);
}
