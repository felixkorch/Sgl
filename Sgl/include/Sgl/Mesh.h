#pragma once
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Material.h"
#include "glm/glm.hpp"
#include "obj_loader/OBJ_Loader.h"

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

		Mesh(const std::string& filePath, const Material& material)
			: material(material)
		{
			objl::Loader loader;
			if (!loader.LoadFile(filePath))
				printf("Could'nt find obj file");

			indexCount = loader.LoadedIndices.size();

			vertexBuffer.Init_StaticDraw(loader.LoadedVertices.data(), loader.LoadedVertices.size() * sizeof(objl::Vertex));
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			vertexArray.AddBuffer(vertexBuffer, layout);
			indexBuffer = new IndexBuffer(loader.LoadedIndices.data(), loader.LoadedIndices.size());

			vertexBuffer.Unbind();
			vertexArray.Unbind();
		}

		Mesh(Vertex* vertices, unsigned int nVertices, unsigned int* indices, unsigned int indexCount, const Material& material)
			: vertexCount(nVertices), indexCount(indexCount), material(material)
		{
			vertexBuffer.Init_StaticDraw(vertices, nVertices * sizeof(Vertex));
			layout.Push<float>(3); // position
			layout.Push<float>(3); // normal
			layout.Push<float>(2); // texture
			vertexArray.AddBuffer(vertexBuffer, layout);
			indexBuffer = new IndexBuffer(indices, indexCount);

			vertexBuffer.Unbind();
			vertexArray.Unbind();
		}

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material)
			: indexCount(indices.size()), material(material)
		{
			vertexBuffer.Init_StaticDraw(vertices.data(), vertices.size() * sizeof(Vertex));
			layout.Push<float>(3); // position
			layout.Push<float>(3); // normal
			layout.Push<float>(2); // texture
			vertexArray.AddBuffer(vertexBuffer, layout);
			indexBuffer = new IndexBuffer(indices.data(), indices.size());

			vertexBuffer.Unbind();
			vertexArray.Unbind();
		}

		~Mesh()
		{
			delete indexBuffer;
		}

		Material& getMaterial()
		{
			return material;
		}

		void draw()
		{
			material.Bind();
			vertexBuffer.Bind();
			vertexArray.Bind();
			indexBuffer->Bind();

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

			indexBuffer->Unbind();
			vertexBuffer.Unbind();
			vertexArray.Unbind();
		}
	};
}