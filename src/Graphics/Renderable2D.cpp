#include "Sgl/Graphics/Texture2D.h"
#include "Sgl/Graphics/Renderable2D.h"
#include "Sgl/Graphics/Renderer2D.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>
#include <vector>

namespace sgl
{
    Renderable2D::Renderable2D()
        : bounds()
        , color(glm::vec4(1))
        , uvs(GetStandardUVs())
        , texture(nullptr)
    {}

    Renderable2D::Renderable2D(const glm::vec2& size, const glm::vec2& pos)
        : bounds(size, pos)
        , color(glm::vec4(1))
        , uvs(GetStandardUVs())
        , texture(nullptr)
    {}

    Renderable2D::Renderable2D(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
        : bounds(size, pos)
        , color(color)
        , uvs(GetStandardUVs())
        , texture(nullptr)
    {}

    Renderable2D::Renderable2D(const glm::vec2& pos, Texture2D* texture)
        : bounds(glm::vec2(texture->GetWidth(), texture->GetHeight()), pos)
        , color(glm::vec4(1))
        , uvs(GetStandardUVs())
        , texture(texture)
    {}

	Renderable2D::Renderable2D(float x, float y, Texture2D* texture)
		: bounds(glm::vec2(texture->GetWidth(), texture->GetHeight()), glm::vec2(x, y))
		, color(glm::vec4(1))
		, uvs(GetStandardUVs())
		, texture(texture)
	{}

	Texture2D* Renderable2D::GetTexture()
    {
        return texture;
    }

    std::array<glm::vec2, 4> Renderable2D::GetStandardUVs()
    {
        return { glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1) };
    }

    const std::array<glm::vec2, 4>& Renderable2D::GetUVs()
    {
        return uvs;
    }

    Rectangle& Renderable2D::GetBounds()
    {
        return bounds;
    }

    const glm::vec4 Renderable2D::GetMinBounds()
    {
        return glm::vec4(bounds.MinBounds(), 1, 1);
    }

    const glm::vec4 Renderable2D::GetMaxBounds()
    {
        return glm::vec4(bounds.MaxBounds(), 1, 1);
    }

    void Renderable2D::SetPos(const glm::vec2& _pos)
    {
        bounds.pos = _pos;
    }

    void Renderable2D::SetPos(float x, float y)
    {
        bounds.pos = glm::vec2(x, y);
    }

    void Renderable2D::SetColor(const glm::vec4& _color)
    {
        color = _color;
    }

    void Renderable2D::SetUV(const std::array<glm::vec2, 4>& _uvs)
    {
        uvs = _uvs;
    }

    void Renderable2D::SetSize(float width, float height)
    {
        bounds.size = glm::vec2(width, height);
    }

    void Renderable2D::Submit(Renderer2D* renderer)
    {
        renderer->Submit(this);
    }

}