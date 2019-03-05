#pragma once
#include "Sgl/VertexArray.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
	struct VertexData {
		glm::vec3 vertexCoord;
		glm::vec4 color;
	};

	class Renderable2D {
	public:
		std::array<VertexData, 4> vertexData;

		constexpr Renderable2D(const VertexData& v1, const VertexData& v2, const VertexData& v3, const VertexData& v4)
			: vertexData{ v1, v2, v3, v4 } {}

		constexpr Renderable2D() : vertexData{} {}


		std::array<VertexData, 4>::iterator begin()
		{
			return vertexData.begin();
		}

		std::array<VertexData, 4>::iterator end()
		{
			return vertexData.end();
		}

		VertexData& operator[](std::size_t offset)
		{
			return vertexData[offset];
		}

		void TranslateX(int val)
		{
			for (auto& a : vertexData)
				a.vertexCoord.x += val;
		}

		void TranslateY(int val)
		{
			for (auto& a : vertexData)
				a.vertexCoord.y += val;
		}
	};
}