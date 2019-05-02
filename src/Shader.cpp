#include "Sgl/OpenGL.h"
#include "Sgl/Shader.h"
#include "Sgl/Log.h"
#include "glm/glm.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace sgl
{
#ifdef SGL_PLATFORM_WEB
    const char* Shader::Renderer2D = {
        #include "Sgl/Shaders/Renderer2D.gles3.shader"
    };
	const char* Shader::GreyScaleShader = {
		#include "Sgl/Shaders/GreyScale.gles3.shader"
	};
#else
    const char* Shader::GreyScaleShader = {
        #include "Sgl/Shaders/GreyScale.shader"
    };
	const char* Shader::Renderer2D = {
		#include "Sgl/Shaders/Renderer2D.shader"
	};
#endif


    Shader::Shader()
		: rendererID(0)
        , filePath("NULL")
    {}

	Shader::~Shader()
	{
        if(rendererID) SGL_CORE_INFO("Shader(id: {}) deleted.", rendererID);
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
			SGL_CORE_WARN("Unable to set Uniform {}, doesn't exist", name);

		uniformLocationCache[name] = location;
		return location;
	}

	void Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		if (vertexShader.empty() || fragmentShader.empty())
			SGL_CORE_ERROR("Vertex or Fragment shader empty.");

		unsigned int program = glCreateProgram();
        SGL_CORE_INFO("Shader(id: {}) created.", program);

		if (program == 0)
			SGL_CORE_ERROR("Program failed to compile");

		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		rendererID = program;
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
			SGL_CORE_WARN("{}, {}", message, type);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	ShaderProgramSource Shader::ParseShader(std::stringstream& str)
	{
		enum class ShaderType {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (std::getline(str, line)) {
			if(line == "")
				continue;
			if (line.find("#shader") != std::string::npos) {

				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;

				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else {
				if (type == ShaderType::NONE) {
					SGL_CORE_ERROR("Invalid shader format. Needs to contain vertex / fragments directives.");
					return {};
				}
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	Shader* Shader::CreateFromFile(const std::string& path)
	{
		Shader* shader = new Shader;
		std::ifstream stream(path);

		if (!stream.good()) {
			SGL_CORE_ERROR("Shader not found, path given: {}", path);
			return nullptr;
		}

		std::stringstream str;
		str << stream.rdbuf();

		ShaderProgramSource source = shader->ParseShader(str);
		shader->CreateShader(source.VertexSource, source.FragmentSource);

		return shader;
	}

	Shader* Shader::CreateFromString(const char* vertexShader, const char* fragmentShader)
	{
		Shader* shader = new Shader;
		shader->CreateShader(vertexShader, fragmentShader);
		return shader;
	}

	Shader* Shader::CreateFromString(const char* program)
	{
		Shader* shader = new Shader;
		std::stringstream str;
		str << program;
		ShaderProgramSource source = shader->ParseShader(str);
		shader->CreateShader(source.VertexSource, source.FragmentSource);
		return shader;
	}

}
