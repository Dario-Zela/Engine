#pragma once
#include "Engine/Renderer/Texture.h"

namespace Engine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		inline virtual unsigned int GetWidth() const override { return mWidth; }
		inline virtual unsigned int GetHeight() const override { return mHeight; }

		virtual void Bind(unsigned int textureSlot = 0) const override;
	private:
		unsigned int mWidth;
		unsigned int mHeight;
		unsigned int mRedererID;
		std::string mPath;
	};
}