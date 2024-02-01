#include <Dream.h>

class ExampleLayer : public Dream::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//DM_INFO("ExampleLayer::Update");

		if (Dream::Input::IsKeyPressed(DM_KEY_TAB))
			DM_TRACE("Tab key is pressed (poll)!");
		
	}

	void OnEvent(Dream::Event& event) override
	{
		//DM_TRACE("{0}", event);

		if (event.GetEventType() == Dream::EventType::KeyPressed)
		{
			Dream::KeyPressedEvent& e = (Dream::KeyPressedEvent&)event;
			if (e.GetKeyCode() == DM_KEY_TAB)
				DM_TRACE("Tab key is pressed (event)!");
			DM_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Dream::Application {

public:
	Sandbox() 
	{
		// issue here if I don't comment this out when trying to dock.
		//PushLayer(new ExampleLayer());
		
	}

	~Sandbox() 
	{

	}
};

Dream::Application* Dream::CreateApplication() 
{
	return new Sandbox();
}