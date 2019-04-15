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
		std::unique_ptr<Material> material;
		unsigned int indexCount;
		unsigned int vertexCount;
	public:
		Mesh(const std::string& filePath);
		Mesh(const Vertex* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount);
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();

		Material& GetMaterial()
		{
			return *material;
		}

		void SetMaterial(std::unique_ptr<Material> _material)
		{
			material = std::move(_material);
		}

		static Obj3D LoadObj(const std::string& filePath);

		void Draw();
	};
}