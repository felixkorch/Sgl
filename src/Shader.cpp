#include "Sgl/OpenGL.h"
#include "Sgl/Shader.h"
#include "Sgl/ShaderUniform.h"
#include "Sgl/Common.h"
#include "glm/glm.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace sgl
{
	Shader::Shader(const std::string& filepath)
		: filePath(filepath), rendererID(0)
	{
		ShaderProgramSource source = ParseShader(filepath);
		rendererID = CreateShader(source.VertexSource, source.FragmentSource);
	}

	Shader::Shader(const char* vertexShader, const char* fragmentShader)
	{
		rendererID = CreateShader(vertexShader, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(rendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(rendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string& name, int v0)
	{
		glUniform1i(GetUniformLocation(name), v0);
	}

	void Shader::SetUniform1iv(const std::string & name, int count, const int* value)
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetUniform1f(const std::string& name, float v0)
	{
		glUniform1f(GetUniformLocation(name), v0);
	}

	void Shader::SetUniform3f(const std::string& name, const glm::vec3& vec3)
	{
		glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (uniformLocationCache.find(name) != uniformLocationCache.end())
			return uniformLocationCache[name];

		int location = glGetUniformLocation(rendererID, name.c_str());
		if (location == -1)
			SglCoreWarn("Unable to set Uniform {}, doesn't exist", name);

		uniformLocationCache[name] = location;
		return location;
	}

	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		if (vertexShader.empty() || fragmentShader.empty())
			SglCoreError("Vertex or Fragment shader empty.");

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

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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
			SglCoreWarn("{}, {}", message, type);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	ShaderProgramSource Shader::ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		if (!stream.good()) {
			SglCoreError("Shader not found, path given: {}", filepath);
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

	void Shader::SetUniformData(UniformHandler& uHandler)
	{
		Bind();

		for (auto& u : uHandler) {
			switch (u.type) {
			case UniformType::Int:
				SetUniform1i(uHandler.GetName<int>(u), uHandler.GetValue<int>(u));
			case UniformType::Vec3:
				SetUniform3f(uHandler.GetName<glm::vec3>(u), uHandler.GetValue<glm::vec3>(u));
			case UniformType::Mat4:
				SetUniformMat4f(uHandler.GetName<glm::mat4>(u), uHandler.GetValue<glm::mat4>(u));
			case UniformType::Float:
				SetUniform1f(uHandler.GetName<float>(u), uHandler.GetValue<float>(u));
			}
		}
	}
}
