#include "dmpch.h"
#include "Application.h"

#include "Input.h"

namespace Dream {

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		DM_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(DM_BIND_EVENT_FN(Application::OnEvent));
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
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//auto [x, y] = Input::GetMousePosition();
			//DM_CORE_TRACE("{0}, {1}", x, y);

			bool isPressed = Input::IsMouseButtonPressed(0);
			bool isAPressed = Input::IsKeyPressed('A');
			if (isPressed) {
				DM_CORE_TRACE("Left Mouse button: {0}", isPressed);
			}
			if(isAPressed){
				DM_CORE_TRACE("A key: {0}", isAPressed);
			}
			
			
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}