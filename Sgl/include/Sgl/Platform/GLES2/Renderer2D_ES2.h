#pragma once
#include "Sgl/Graphics/Renderer2D.h"
#include "Sgl/Graphics/Renderable2D.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBuffer.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Shader.h"

#include <array>

namespace sgl
{
	class Renderer2D_ES2 : public Renderer2D {
	private:
		std::vector<VertexData> vertexDataBuffer;
	public:
		Renderer2D_ES2(unsigned int width, unsigned int height, const Shader& shader);
		~Renderer2D_ES2();
		Renderer2D_ES2(const Renderer2D_ES2&) = delete;
		virtual void operator=(const Renderer2D_ES2&) = delete;

		virtual void Begin() override;
		virtual void Submit(Renderable2D& renderable) override;
		virtual void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2,const glm::vec3& p3, const glm::vec4& color) override;
		virtual void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1)) override;
		virtual void End() override;
		virtual void Flush() override;
		virtual void MoveCamera(const glm::vec2& val) override;
		void SubmitTexture(const Texture2D* texture) override;
	private:
		void Init();
	};
}