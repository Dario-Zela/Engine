#pragma once
#include <string>

namespace Engine 
{
	class ENGINE_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbuind() const = 0;
		
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Shader* Create(const std::string& filePath);
	};
}