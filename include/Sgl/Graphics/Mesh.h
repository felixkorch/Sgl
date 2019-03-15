#pragma once
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Graphics/Material.h"
#include "glm/glm.hpp"

#include <string>

namespace sgl
{
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture;
	};

	struct Obj3D {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

	class Mesh {
	private:
		VertexBufferLayout layout;
		VertexBuffer vertexBuffer;
		VertexArray vertexArray;
		IndexBuffer indexBuffer;
		Material material;
		unsigned int indexCount;
		unsigned int vertexCount;
	public:

		Mesh(const std::string& filePath, const Material& material);
		Mesh(const Vertex* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount, const Material& material);
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material);
		~Mesh();

		Material& GetMaterial()
		{
			return material;
		}

		void SetMaterial(const Material& other)
		{
			material = other;
		}

		static Obj3D LoadObj(const std::string& filePath);

		void Draw();
	};
}