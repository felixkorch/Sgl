#pragma once
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBuffer.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Graphics/Renderable2D.h"
#include "Sgl/Graphics/Texture2D.h"

#include <array>

namespace sgl
{
	class Renderer2D {
	protected:
		static constexpr std::size_t MaxSprites = 1000;
		static constexpr std::size_t VertexSize = sizeof(VertexData);
		static constexpr std::size_t SpriteSize = (4 * VertexSize);
		static constexpr std::size_t BufferSize = SpriteSize * MaxSprites;
		static constexpr std::size_t IndicesCount = (6 * MaxSprites);
		static constexpr std::size_t MaxTextures = 16;

		VertexBufferLayout layout;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		std::unique_ptr<Shader> shader;
		glm::vec2 screenSize;
		Camera2D camera;
        int indexCount;
		std::vector<const Texture2D*> textures;

	public:
        Renderer2D(int width, int height) :
            screenSize(width, height),
            camera(glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f)),
            indexCount(0)
		{
			textures.reserve(MaxTextures);
		}

        virtual ~Renderer2D() = default;
		virtual void Begin() = 0;
		virtual void Init() = 0;
		virtual void Submit(Renderable2D& renderable) = 0;
		virtual void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color) = 0;
		virtual void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1)) = 0;
		virtual void End() = 0;
		virtual void Flush() = 0;
		virtual void SubmitTexture(const Texture2D* texture) = 0;

		void SetCamera(const glm::vec2& val)
		{
			camera.GetPos() = glm::vec3(val, 0);
		}

        void SetShader(std::unique_ptr<Shader> _shader)
        {
            shader = std::move(_shader);
        }

        template <typename ... Args>
        void CreateShader(Args&& ... args)
        {
            shader = std::unique_ptr<Shader>(new Shader(std::forward<Args>(args)...));
        }

		Camera2D& GetCamera()
		{
			return camera;
		}

		void SetScreenSize(int width, int height)
		{
			screenSize.x = width;
			screenSize.y = height;
			camera = Camera2D(width, height);
		}

		static Renderer2D* Create(int width, int height);
	};
}
