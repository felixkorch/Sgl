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
		const auto obj = LoadObj(filePath);
		Mesh(obj.vertices, obj.indices, material);
	}

	Mesh::Mesh(const Vertex* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount, const Material& material)
		: vertexCount(vertexCount), indexCount(indexCount), material(material)
	{
		vertexBuffer.InitStaticDraw(vertices, vertexCount * sizeof(Vertex));
		layout.Push<float>(3); // Position
		layout.Push<float>(3); // Normal
		layout.Push<float>(2); // Texture
		vertexArray.AddBuffer(vertexBuffer, layout);
		indexBuffer.Init(indices, indexCount);

		vertexBuffer.Unbind();
		vertexArray.Unbind();
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material)
		: Mesh(vertices.data(), vertices.size(), indices.data(), indices.size(), material) {}

	Mesh::~Mesh() {}

	Obj3D Mesh::LoadObj(const std::string& filePath)
	{
		SglAssert(false, "NOT IMPEMENTED");
		objl::Loader loader;
		if (!loader.LoadFile(filePath))
			SglWarn("Couldn't find obj file ({})", filePath);

		/*
		TODO NOT IMPLEMENTED
		*/
		return Obj3D{ };
	}

	void Mesh::Draw()
	{
		material.Bind();
		vertexBuffer.Bind();
		vertexArray.Bind();
		indexBuffer.Bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

		indexBuffer.Unbind();
		vertexBuffer.Unbind();
		vertexArray.Unbind();
	}
}