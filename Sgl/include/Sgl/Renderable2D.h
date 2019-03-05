#pragma once
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

		constexpr Renderable2D(VertexData v1, VertexData v2, VertexData v3, VertexData v4)
			: vertexData{ v1, v2, v3, v4 } {}

		constexpr Renderable2D(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const glm::vec4& color)
			: vertexData{ VertexData{ v1, color }, VertexData{ v2, color }, VertexData{ v3, color }, VertexData{ v4, color } } {}

		constexpr Renderable2D() : vertexData{} {}

		static Renderable2D CreateRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1))
		{
			const glm::vec3 v1 = glm::vec3(pos, 1);
			const glm::vec3 v2 = glm::vec3(pos.x + size.x, pos.y, 1);
			const glm::vec3 v3 = glm::vec3(pos.x + size.x, pos.y + size.y, 1);
			const glm::vec3 v4 = glm::vec3(pos.x , pos.y + size.y, 1);
			return Renderable2D(v1, v2, v3, v4, color);
		}

		void SetColor(const glm::vec4& color)
		{
			for (auto& a : vertexData)
				a.color = color;
		}

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