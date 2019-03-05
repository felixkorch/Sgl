#shader vertex
#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textCoord;

out vec3 f_Normal;
out vec3 f_Position;
out vec2 f_TextCoord;

uniform mat4 u_Proj;
uniform mat4 u_Model;

void main() {

	gl_Position = u_Proj * vec4(position, 1.0);
	f_Normal = normal;
	f_Position = vec3(u_Model * vec4(position, 1.0));
	f_TextCoord = textCoord;

}

#shader fragment
#version 300 es

precision highp float;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 f_Normal;
in vec3 f_Position;
in vec2 f_TextCoord;

out vec4 fragColor;

uniform vec3 u_CameraPos;
uniform Light u_Light;
uniform Material u_Material;
uniform sampler2D u_Slot;

void main() {

	vec3 ambient = u_Light.ambient * u_Material.ambient;
	//----------------------------------------------------- ambient

	vec3 unitNormal = normalize(f_Normal);
	vec3 lightDir = normalize(u_Light.position - f_Position);

	float diff = max(dot(unitNormal, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * (diff * u_Material.diffuse);
	//----------------------------------------------------- diffuse

	vec3 viewDir = normalize(u_CameraPos - f_Position);
	vec3 reflectDir = reflect(-lightDir, unitNormal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * (spec * u_Material.specular);
	//----------------------------------------------------- specular

	fragColor = vec4(ambient + diffuse + specular, 1.0) * texture(u_Slot, f_TextCoord); // only textures allowed
}
