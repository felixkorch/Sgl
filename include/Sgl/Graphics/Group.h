#pragma once
#include "Sgl/Graphics/Renderable2D.h"

namespace sgl {
    class Group {
        std::vector<Renderable2D*> children;
        glm::mat4 transformationMatrix;
    public:
        Group(const glm::mat4& matrix);

        void Submit(Renderer2D* renderer);
        void Add(Renderable2D* renderable);
        glm::mat4& GetTransform();
    };
}