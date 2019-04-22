#include "Sgl/Graphics/Renderable2D.h"
#include "Sgl/Graphics/Texture2D.h"
#include "Sgl/Graphics/Sprite.h"

namespace sgl {
    Sprite::Sprite()
        : Renderable2D()
    {}

    Sprite::Sprite(float x, float y, Texture2D* texture)
        : Renderable2D(glm::vec2(x, y), texture)
    {}

    Sprite::Sprite(float width, float height, float x, float y, const glm::vec4& color)
        : Renderable2D(glm::vec2(width, height), glm::vec2(x, y), color)
    {}

    Sprite::Sprite(const glm::vec2 size, const glm::vec2& pos, const glm::vec4& color)
        : Renderable2D(size, pos, color)
    {}

}