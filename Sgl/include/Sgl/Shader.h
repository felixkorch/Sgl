#pragma once

#include "Sgl/ShaderUniform.h"
#include "Sgl/Light.h"
#include "Sgl/Common.h"
#include "glm/glm.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace sgl
{
	struct VertexUniforms {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
	};

	struct FragmentUniforms {
		glm::vec3 cameraPos;
		glm::vec3 lightPos;
		Light lightProps;
	};

	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader {
	private:
		unsigned int rendererID;
		std::string filePath;
		std::unordered_map<std::string, int> uniformLocationCache;
	public:

		Shader(const std::string& filepath)
			: filePath(filepath), rendererID(0)
		{
			ShaderProgramSource source = ParseShader(filepath);
			rendererID = CreateShader(source.VertexSource, source.FragmentSource);
		}

		~Shader()
		{
			glDeleteProgram(rendererID);
		}

		void Bind() const
		{
			glUseProgram(rendererID);
		}

		void Unbind() const
		{
			glUseProgram(0);
		}

		void SetUniform1i(const std::string& name, int v0)
		{
			glUniform1i(GetUniformLocation(name), v0);
		}

		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
		{
			glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
		}

		void SetUniformMat4f(const std::string& name, const glm::mat4& mat)
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
		}

		void SetSystemUniforms(const VertexUniforms* vUniforms, const FragmentUniforms* fUniforms)
		{
			Bind();

			SetUniformMat4f("u_Model", vUniforms->model);
			SetUniformMat4f("u_Proj", vUniforms->view * vUniforms->model);
			SetUniform3f("u_CameraPos", fUniforms->cameraPos);
			SetUniform3f("u_LightPos", fUniforms->lightPos);
			SetUniform3f("u_Light.ambient", fUniforms->lightProps.ambient);
			SetUniform3f("u_Light.diffuse", fUniforms->lightProps.diffuse);
			SetUniform3f("u_Light.specular", fUniforms->lightProps.specular);
		}

		void SetUniform1f(const std::string& name, float v0)
		{
			glUniform1f(GetUniformLocation(name), v0);
		}

		void SetUniform3f(const std::string& name, const glm::vec3& vec3)
		{
			glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
		}

		int GetUniformLocation(const std::string& name)
		{
			if (uniformLocationCache.find(name) != uniformLocationCache.end())
				return uniformLocationCache[name];

			int location = glGetUniformLocation(rendererID, name.c_str());
			if (location == -1)
				SglError("Uniform {} doesn't exist!", name);

			uniformLocationCache[name] = location;
			return location;
		}

		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
		{
			if (vertexShader.empty() || fragmentShader.empty())
				SglError("Vertex or Fragment shader empty.");

			unsigned int program = glCreateProgram();
			unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
			unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

			glAttachShader(program, vs);
			glAttachShader(program, fs);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vs);
			glDeleteShader(fs);

			return program;
		}

		unsigned int CompileShader(unsigned int type, const std::string& source)
		{
			unsigned int id = glCreateShader(type);
			const char* src = source.c_str();
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);

			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(id, length, &length, message);
				SglWarn("{}, {}", message, type);
				glDeleteShader(id);
				return 0;
			}

			return id;
		}

		ShaderProgramSource ParseShader(const std::string& filepath)
		{
			std::ifstream stream(filepath);

			if (!stream.good()) {
				SglError("Shader not found, path given: {}", filepath);
			}

			enum class ShaderType {
				NONE = -1, VERTEX = 0, FRAGMENT = 1
			};

			std::string line;
			std::stringstream ss[2];
			ShaderType type = ShaderType::NONE;

			while (getline(stream, line)) {
				if (line.find("#shader") != std::string::npos) {

					if (line.find("vertex") != std::string::npos)
						type = ShaderType::VERTEX;

					else if (line.find("fragment") != std::string::npos)
						type = ShaderType::FRAGMENT;
				}
				else {
					ss[(int)type] << line << '\n';
				}
			}

			return { ss[0].str(), ss[1].str() };
		}

		void SetUniformData(const std::vector<UniformDeclaration>& declarations, const char* data)
		{
			Bind();

			for (auto u : declarations) {
				switch (u.type) {
				case UniformType::Int:
					SetUniform1i(u.name, *(int*)(data + u.offset));
					break;
				case UniformType::Float:
					SetUniform1f(u.name, *(float*)(data + u.offset));
					break;
				case UniformType::Vec3:
					SetUniform3f(u.name, *(glm::vec3*)(data + u.offset));
					break;
				default:
					break;
				}
			}
		}
	};
}