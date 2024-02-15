#include "dmpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Dream {
	
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
	
}