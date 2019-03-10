#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoordinates;

out vec2 f_texCoordinates;

void main() {
    f_texCoordinates = texCoordinates;
    gl_Position = position;
}

#shader fragment
#version 330 core

uniform sampler2D f_Sampler;

in vec2 f_texCoordinates;

out vec4 color;

void main() {
    color = texture(f_Sampler, f_texCoordinates);
}