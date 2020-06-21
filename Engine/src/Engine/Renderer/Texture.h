#pragma once
#include "Engine/Core.h"
#include <string>

namespace Engine
{
	class ENGINE_API Texture
	{
	public:
		~Texture() = default;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void Bind(unsigned int textureSlot = 0) const = 0;
	};

	class ENGINE_API Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}