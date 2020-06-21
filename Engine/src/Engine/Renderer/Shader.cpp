#include "ENPH.h"
#include "Shader.h"
#include "OpenGL/OpenGLShader.h"
#include "Engine/Renderer/Render.h"

namespace Engine
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetCurrenAPI())
		{
		case RendererAPI::API::None: EN_CORE_ASSERT(false, "No Renderer API has been selected"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			break;
		}
		EN_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetCurrenAPI())
		{
		case RendererAPI::API::None: EN_CORE_ASSERT(false, "No Renderer API has been selected"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(filePath);
		default:
			break;
		}
		EN_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}