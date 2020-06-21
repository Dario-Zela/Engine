#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Engine/Renderer/Shader.h"

//To Remove
#include "Engine/Core.h"
typedef unsigned int GLenum;

namespace Engine
{
	class ENGINE_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		inline virtual const std::string& GetName() const override { return mName; }
		virtual void Bind() const override;
		virtual	void Unbuind() const override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		
		void UploadUniformVecF4(const std::string& name, const glm::vec4& values);
		void UploadUniformVecF3(const std::string& name, const glm::vec3& values);
		void UploadUniformVecF2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat(const std::string& name, float value);
		
		void UploadUniformInt(const std::string& name, int value);

	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProccess(const std::string& shaderSrc);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		GLenum ShaderTypeFromString(const std::string& type);

		std::string mName;
		unsigned int mRendererID;
	};
}