#pragma once
#include "Sgl/Mesh.h"
#include "Sgl/Transform.h"
#include "Sgl/Material.h"

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

		inline glm::mat4 getModelMatrix() const { return transform.getModel(); };
		inline Transform& getTransform() { return transform; };
		inline std::shared_ptr<Mesh>& getMesh() { return mesh; };
	};
}