#include "ENPH.h"
#include "RenderCommand.h"

#include "OpenGL/OpenGLRendererAPI.h"

namespace Engine
{
	RendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;
}