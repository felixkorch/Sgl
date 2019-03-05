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
		unsigned int nVertices;
		glm::vec3 m_Pos;
		VertexArray m_VA;
		VertexBuffer m_VB;
		VertexBufferLayout m_Layout;
		IndexBuffer* m_IB;
		unsigned int m_IndexCount;
		Material m_Material;
	public:

		Mesh(const std::string& filePath, const Material& material)
			: m_Material(material)
		{
			objl::Loader loader;
			if (!loader.LoadFile(filePath))
				printf("Could'nt find obj file");

			m_IndexCount = loader.LoadedIndices.size();

			m_VB.Init_StaticDraw(loader.LoadedVertices.data(), loader.LoadedVertices.size() * sizeof(objl::Vertex));
			m_Layout.Push<float>(3);
			m_Layout.Push<float>(3);
			m_Layout.Push<float>(2);
			m_VA.AddBuffer(m_VB, m_Layout);
			m_IB = new IndexBuffer(loader.LoadedIndices.data(), loader.LoadedIndices.size());

			m_VB.Unbind();
			m_VA.Unbind();
		}

		Mesh(Vertex* vertices, unsigned int nVertices, unsigned int* indices, unsigned int indexCount, const Material& material)
			: nVertices(nVertices), m_IndexCount(indexCount), m_Material(material)
		{
			m_VB.Init_StaticDraw(vertices, nVertices * sizeof(Vertex));
			m_Layout.Push<float>(3); // position
			m_Layout.Push<float>(3); // normal
			m_Layout.Push<float>(2); // texture
			m_VA.AddBuffer(m_VB, m_Layout);
			m_IB = new IndexBuffer(indices, indexCount);

			m_VB.Unbind();
			m_VA.Unbind();
		}

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material)
			: m_IndexCount(indices.size()), m_Material(material)
		{
			m_VB.Init_StaticDraw(vertices.data(), vertices.size() * sizeof(Vertex));
			m_Layout.Push<float>(3); // position
			m_Layout.Push<float>(3); // normal
			m_Layout.Push<float>(2); // texture
			m_VA.AddBuffer(m_VB, m_Layout);
			m_IB = new IndexBuffer(indices.data(), indices.size());

			m_VB.Unbind();
			m_VA.Unbind();
		}

		~Mesh()
		{
			delete m_IB;
		}

		Material& getMaterial()
		{
			return m_Material;
		}

		void draw()
		{
			m_Material.Bind();
			m_VB.Bind();
			m_VA.Bind();
			m_IB->Bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);

			m_IB->Unbind();
			m_VB.Unbind();
			m_VA.Unbind();
		}
	};
}