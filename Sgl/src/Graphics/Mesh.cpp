#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Mesh.h"
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Graphics/Material.h"
#include "Sgl/Common.h"
#include "obj_loader/OBJ_Loader.h"
#include <string>

namespace sgl
{
	Mesh::Mesh(const std::string& filePath, const Material& material)
		: material(material)
	{
		objl::Loader loader;
		if (!loader.LoadFile(filePath))
			SglWarn("Couldn't find obj file ({})", filePath);

		indexCount = loader.LoadedIndices.size();

		vertexBuffer.InitStaticDraw(loader.LoadedVertices.data(), loader.LoadedVertices.size() * sizeof(objl::Vertex));
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		vertexArray.AddBuffer(vertexBuffer, layout);
		indexBuffer->Init(loader.LoadedIndices.data(), loader.LoadedIndices.size());

		vertexBuffer.Unbind();
		vertexArray.Unbind();
	}

	Mesh::Mesh(Vertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount, const Material& material)
		: vertexCount(vertexCount), indexCount(indexCount), material(material)
	{
		vertexBuffer.InitStaticDraw(vertices, vertexCount * sizeof(Vertex));
		layout.Push<float>(3); // Position
		layout.Push<float>(3); // Normal
		layout.Push<float>(2); // Texture
		vertexArray.AddBuffer(vertexBuffer, layout);
		indexBuffer->Init(indices, indexCount);

		vertexBuffer.Unbind();
		vertexArray.Unbind();
	}

	Mesh::~Mesh()
	{
		delete indexBuffer;
	}

	void Mesh::Draw()
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
}