R"(
#shader vertex
#version 300 es

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * vec4(aPos, 1.0);
    TexCoords = aTexCoords;
}  

#shader fragment
#version 300 es

precision mediump float;

out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D u_Sampler;

void main()
{ 
    FragColor = texture(u_Sampler, TexCoords);
    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    FragColor = vec4(average, average, average, 1.0);
}

)"
