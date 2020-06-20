#pragma once
#include <string>

namespace Engine 
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbuind();
	private:
		unsigned int mRendererID;
	};
}