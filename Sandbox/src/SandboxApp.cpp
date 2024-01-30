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

		bool isPressed = Dream::Input::IsMouseButtonPressed(DM_MOUSE_BUTTON_1);
		bool isAPressed = Dream::Input::IsKeyPressed(DM_KEY_A);
		if (isPressed) {
			DM_CORE_TRACE("Left Mouse button: {0}", isPressed);
		}
		if (isAPressed) {
			DM_CORE_TRACE("A key: {0}", isAPressed);
		}
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