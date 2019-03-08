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
		unsigned int vertexCount;
		glm::vec3 pos;
		VertexArray vertexArray;
		VertexBuffer vertexBuffer;
		VertexBufferLayout layout;
		IndexBuffer* indexBuffer;
		unsigned int indexCount;
		Material material;
	public:

		Mesh(const std::string& filePath, const Material& material);
		Mesh(Vertex* vertices, unsigned int nVertices, unsigned int* indices, unsigned int indexCount, const Material& material);
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

		void Draw();
	};
}