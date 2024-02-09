#include "dmpch.h"
#include "Application.h"

#include "Input.h"

#include "glad/glad.h"

namespace Dream {

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		DM_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(DM_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Rendering triangle
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,

		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		
		// This draws a square by drawing 2 triangles made of indices 0, 1, 2 and 0, 3 ,1 with anti-clockwise winding.
		// unsigned int indices[6] = { 0 , 1 , 2 , 0 , 3, 1};

		// code for 1 triangle
		uint32_t indices[3] = { 0 , 1 , 2};
		m_IndexBuffer.reset(IndexBuffer::Create(indices, std::size(indices)));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				if (v_Position.x < 0.0)
				{
					v_Position.x = v_Position.x * -1.0;
					
				}
				else if (v_Position.y < 0.0)
				{
					v_Position.z = v_Position.y * -1.0;
					v_Position.x = 0;
				}
				
				
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;			

			in vec3 v_Position;			

			void main()
			{
				color = vec4(v_Position, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application() 
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(DM_BIND_EVENT_FN(Application::OnWindowClose));

		DM_CORE_TRACE("{0}", e);

		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) 
		{
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
		
	}


	void Application::Run() 
	{
		while (m_Running) 
		{
			
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, (void*)0);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//auto [x, y] = Input::GetMousePosition();
			//DM_CORE_TRACE("{0}, {1}", x, y);	
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}