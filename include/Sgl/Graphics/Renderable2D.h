#pragma once
#include "Sgl/Graphics/Texture2D.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>
#include <vector>

namespace sgl
{
	struct VertexData {
		glm::vec3 vertex;
		glm::vec4 color;
		glm::vec2 uv;
		float tid;
	};

    class Renderer2D;

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

		const glm::vec2 MinBounds() const
		{
			return pos;
		}

		const glm::vec2 MaxBounds() const
		{
			return glm::vec2(pos.x + size.x, pos.y + size.y);
		}
	};

	class Renderable2D {
    protected:
		Rectangle bounds;
		glm::vec4 color;
		std::array<glm::vec2, 4> uvs;
        Texture2D* texture;
    public:
        Renderable2D();
        Renderable2D(const glm::vec2& size, const glm::vec2& pos);
        Renderable2D(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color);
        Renderable2D(const glm::vec2& pos, Texture2D* texture);
        Renderable2D(float x, float y, Texture2D* texture);
        virtual ~Renderable2D() = default;

        // Getters
        Texture2D* GetTexture();
        const std::array<glm::vec2, 4>& GetUVs();
        const glm::vec4& GetColor() { return color; }
        const glm::vec4 GetMinBounds();
        const glm::vec4 GetMaxBounds();

        // Setters
        void SetPos(const glm::vec2& _pos);
        void SetPos(float x, float y);
        void SetColor(const glm::vec4& _color);
        void SetUV(const std::array<glm::vec2, 4>& _uvs);
        void SetSize(float width, float height);

        void Submit(Renderer2D* renderer);

        static std::array<glm::vec2, 4> GetStandardUVs();
	};

}