#pragma once
#include "Sgl/ShaderUniform.h"
#include "Sgl/Graphics/Light.h"
#include <string>
#include <unordered_map>

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
		Shader(const std::string& filepath);
		~Shader();
		void Bind() const;
		void Unbind() const;
		void SetUniform1i(const std::string& name, int v0);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
		void SetSystemUniforms(const VertexUniforms* vUniforms, const FragmentUniforms* fUniforms);
		void SetUniform1f(const std::string& name, float v0);
		void SetUniform3f(const std::string& name, const glm::vec3& vec3);
		int GetUniformLocation(const std::string& name);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		ShaderProgramSource ParseShader(const std::string& filepath);
		void SetUniformData(const std::vector<UniformDeclaration>& declarations, const char* data);
	};
}