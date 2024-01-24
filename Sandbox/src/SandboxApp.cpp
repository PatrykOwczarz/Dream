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
		DM_INFO("ExampleLayer::Update");
	}

	void OnEvent(Dream::Event& event) override
	{
		DM_TRACE("{0}", event);
	}
};

class Sandbox : public Dream::Application {

public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Dream::ImGuiLayer());
	}

	~Sandbox() 
	{

	}
};

Dream::Application* Dream::CreateApplication() 
{
	return new Sandbox();
}