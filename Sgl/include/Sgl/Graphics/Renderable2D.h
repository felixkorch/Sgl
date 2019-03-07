#pragma once
#include "Sgl/Graphics/Transform.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
	struct VertexData {
		glm::vec3 vertexCoord;
		glm::vec4 color;
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
		glm::vec4 color;

		Renderable2D() {}

		Renderable2D(const glm::vec2& size, const glm::vec2& pos)
			: bounds(size, pos), color(glm::vec4(1, 1, 1, 1)) {}

		constexpr Renderable2D(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
			: bounds(size, pos), color(color) {}

		void SetPos(const glm::vec2& pos)
		{
			bounds.pos = pos;
		}
	};

}