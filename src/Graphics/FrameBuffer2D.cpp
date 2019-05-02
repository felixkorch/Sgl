#include "Sgl/Graphics/Framebuffer2D.h"
#include "Sgl/OpenGL.h"
#include "Sgl/Log.h"

namespace sgl {

	FrameBuffer2D::FrameBuffer2D(int width, int height)
		: texture(Texture2D::Create(width, height))
		, width(width)
		, height(height)
	{
		// Create a framebuffer and attach a texture as color buffer.
		glGenFramebuffers(1, &frameBufferHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetHandle(), 0);

		// Create a render buffer to store depth data
		glGenRenderbuffers(1, &depthBufferHandle);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBufferHandle);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferHandle); // No stencil attachment atm.

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			SGL_CORE_INFO("Framebuffer not complete!");

		// Unbind the framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer2D::~FrameBuffer2D()
	{
		glDeleteFramebuffers(1, &frameBufferHandle);
	}

	void FrameBuffer2D::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
		//glViewport(0, 0, width, height);
	}

	void FrameBuffer2D::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer2D::Clear()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


}

