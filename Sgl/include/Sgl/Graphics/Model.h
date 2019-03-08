#pragma once
#include "Sgl/Graphics/Mesh.h"
#include "Sgl/Graphics/Transform.h"
#include "Sgl/Graphics/Material.h"

#include <string>
#include <memory>

namespace sgl
{
	class Model {
	private:
		std::shared_ptr<Mesh> mesh;
		Transform transform;
	public:
		Model(const std::shared_ptr<Mesh>& mesh, const Transform& transform = Transform())
			: mesh(mesh), transform(transform) {}

		Model(const std::string& obj, const Material& material, const Transform& transform = Transform())
			: mesh(std::make_shared<Mesh>(obj, material)), transform(transform) {}

		glm::mat4 GetModelMatrix() const { return transform.GetModelMatrix(); };
		Transform& GetTransform() { return transform; };
		std::shared_ptr<Mesh>& GetMesh() { return mesh; };
	};
}