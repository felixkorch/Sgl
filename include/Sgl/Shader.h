#pragma once
#include "Sgl/ShaderUniform.h"
#include "Sgl/Graphics/Light.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace sgl
{
	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader {
	public:
		/* Some simple shader programs */
		static const char* Core_Vertex_Shader2D;
		static const char* Core_Fragment_Shader2D;
		static const char* GLES2_Vertex_Shader2D;
		static const char* GLES2_Fragment_Shader2D;
	private:
		unsigned int rendererID;
		std::string filePath;
		std::unordered_map<std::string, int> uniformLocationCache;
	public:
		Shader(const std::string& filepath);
		Shader(const char* vertexShader, const char* fragmentShader);
		~Shader();
		void Bind() const;
		void Unbind() const;
		void SetUniform1i(const std::string& name, int v0);
		void SetUniform1iv(const std::string& name, int count, const int* value);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
		void SetUniform1f(const std::string& name, float v0);
		void SetUniform3f(const std::string& name, const glm::vec3& vec3);
		int GetUniformLocation(const std::string& name);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		ShaderProgramSource ParseShader(const std::string& filepath);
		void SetUniformData(UniformHandler& uniformHandler);

		unsigned int GetRendererID()
		{
			return rendererID;
		}
	};
}
