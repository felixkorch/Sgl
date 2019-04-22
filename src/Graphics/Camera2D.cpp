#pragma once
#include "Sgl/Log.h"
#include "Sgl/Graphics/Camera2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace sgl
{
    constexpr Camera2D::Camera2D(const glm::mat4& ortho)
        : ortho(ortho), pos{} {}

    Camera2D::Camera2D(const glm::vec2& size)
        : ortho(glm::ortho(0.0f, size.x, 0.0f, size.y, -1.0f, 1.0f))
        , pos{}
    {}

    Camera2D::Camera2D(int width, int height)
        : Camera2D(glm::vec2(width, height))
    {}

    std::unique_ptr<Camera2D> Camera2D::Create(int width, int height)
    {
        return std::unique_ptr<Camera2D>(new Camera2D(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f)));
    }
}
