#pragma once
#include "Sgl/Graphics/Transform.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
	struct VertexData {
		glm::vec3 vertex;
		glm::vec4 color;
		glm::vec2 uv;
		float tid;
	};

	class Rectangle {
	public:
		glm::vec2 size;
		glm::vec2 pos;

		constexpr Rectangle(const glm::vec2& size, const glm::vec2& pos)
			: size(size), pos(pos) {}

		Rectangle()
			: size(0), pos(0) {}

		bool Contains(const glm::vec2& point)
		{
			return (point.x >= pos.x && point.x <= pos.x + size.x) && (point.y >= pos.y && point.y <= pos.y + size.y);
		}

		bool Intersects(const Rectangle& other)
		{
			if (other.pos.x > pos.x || pos.x > other.pos.x)
				return false;
			if (other.pos.y < pos.y || pos.y < other.pos.y)
				return false;

			return true;
		}

		const glm::vec2 MinBounds()
		{
			return pos;
		}

		const glm::vec2 MaxBounds()
		{
			return glm::vec2(pos.x + size.x, pos.y + size.y);
		}
	};

	class Renderable2D {
	public:
		Rectangle bounds;
		glm::vec4 color = glm::vec4(1);
		std::vector<glm::vec2> uv = GetStandardUVs();
		float tid = 0;

		Renderable2D() {}

		Renderable2D(const glm::vec2& size, const glm::vec2& pos)
			: bounds(size, pos) {}

		Renderable2D(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
			: bounds(size, pos), color(color) {}

		void SetPos(const glm::vec2& pos)
		{
			bounds.pos = pos;
		}

		const std::array<glm::vec3, 4> GetVertices()
		{
			const glm::vec3 boundsMin = glm::vec3(bounds.MinBounds(), 1);
			const glm::vec3 boundsMax = glm::vec3(bounds.MaxBounds(), 1);
			return {
				boundsMin, glm::vec3(boundsMin.x + bounds.size.x, boundsMin.y, 1),
				boundsMax, glm::vec3(boundsMin.x, boundsMin.y + bounds.size.y, 1)
			};
		}

		static std::vector<glm::vec2> GetStandardUVs()
		{
			return { glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0) };
		}
	};

}