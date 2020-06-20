#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Engine 
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbuind();

		void UploadUniformMat4(const std::string& name ,const glm::mat4& matrix);
	private:
		unsigned int mRendererID;
	};
}