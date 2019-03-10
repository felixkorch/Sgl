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

	class Mesh {
	private:
		VertexBufferLayout layout;
		VertexBuffer vertexBuffer;
		VertexArray vertexArray;
		IndexBuffer* indexBuffer;
		Material material;
		unsigned int indexCount;
		unsigned int vertexCount;
	public:

		Mesh(const std::string& filePath, const Material& material);
		Mesh(Vertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount, const Material& material);
		~Mesh();

		Material& GetMaterial()
		{
			return material;
		}

		void SetMaterial(const Material& other)
		{
			material = other;
		}

		void Draw();
	};
}