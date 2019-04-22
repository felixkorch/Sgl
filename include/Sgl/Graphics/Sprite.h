#include "Sgl/Graphics/Renderable2D.h"
#include "Sgl/Graphics/Texture2D.h"

namespace sgl {

    class Sprite : public Renderable2D {
    public:
        Sprite();
        Sprite(float x, float y, Texture2D* texture);
        Sprite(float width, float height, float x, float y, const glm::vec4& color);
        Sprite(const glm::vec2 size, const glm::vec2& pos, const glm::vec4& color);

        void SetTexture(Texture2D* _texture) { texture = _texture; }
    };

}