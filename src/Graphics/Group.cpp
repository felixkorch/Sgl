#include "Sgl/Graphics/Group.h"
#include "Sgl/Graphics/Renderer2D.h"

namespace sgl {
    Group::Group(const glm::mat4& matrix)
        : children()
        , transformationMatrix(matrix)
    {}

    void Group::Submit(Renderer2D* renderer)
    {
        renderer->Push(transformationMatrix, false);

        for (auto& child : children)
            child->Submit(renderer);

        renderer->Pop();
    }

    void Group::Add(Renderable2D* renderable)
    {
        children.push_back(renderable);
    }

    glm::mat4& Group::GetTransform()
    {
        return transformationMatrix;
    }
}