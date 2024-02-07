#include "dmpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Dream {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		DM_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DM_CORE_ASSERT(status, "Failed to initialize Glad!");

		// OpenGL and Graphics info
		DM_CORE_INFO("OpenGL Info:");
		DM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		DM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		DM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
		
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}