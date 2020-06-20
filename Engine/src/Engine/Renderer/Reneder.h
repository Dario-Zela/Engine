#pragma once

namespace Engine
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer 
	{
	public:
		inline static RendererAPI GetCurrenAPI() { return sRendererAPI; }
	private:
		static RendererAPI sRendererAPI;
	};
}