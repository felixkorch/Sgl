#pragma once
#include "Sgl/Graphics/Texture2D.h"
#include <memory>

namespace sgl {
	class FrameBuffer2D {
		unsigned int frameBufferHandle, depthBufferHandle;
		std::unique_ptr<Texture2D> texture;
		int width, height;

	protected:
		FrameBuffer2D(FrameBuffer2D&& other);
		FrameBuffer2D& operator=(FrameBuffer2D&& other);
		FrameBuffer2D(const FrameBuffer2D& other);
		FrameBuffer2D& operator=(const FrameBuffer2D& other);
	public:
		FrameBuffer2D(int width, int height);
		~FrameBuffer2D();

		void Bind();
		void Unbind();
		void Clear();

		Texture2D* GetTexture() { return texture.get(); }
	};
}