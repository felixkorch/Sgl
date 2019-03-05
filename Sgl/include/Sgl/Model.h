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
		std::shared_ptr<Mesh> m_Mesh;
		Transform m_Transform;
	public:
		Model(const std::shared_ptr<Mesh>& mesh, const Transform& transform = Transform())
			: m_Mesh(mesh), m_Transform(transform) {}

		Model(const std::string& obj, const Material& material, const Transform& transform = Transform())
			: m_Mesh(std::make_shared<Mesh>(obj, material)), m_Transform(transform) {}

		inline glm::mat4 getModelMatrix() const { return m_Transform.getModel(); };
		inline Transform& getTransform() { return m_Transform; };
		inline std::shared_ptr<Mesh>& getMesh() { return m_Mesh; };
	};
}