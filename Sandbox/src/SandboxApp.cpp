#include <Dream.h>

#include "imgui/imgui.h"

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

	virtual void OnImGuiRender() override
	{
		// Requires Linking fix, Will convert Dream engine to a static library on Monday.
		// DLL has its own benefits but since all of the current vendor packages are static libraries, it would require
		// workarounds to make Dream compatible with them in the sandbox app project.
		// Could make a definition file but converting into a static library has its own benefits too.
		// Some benefits would be no export/import macros, the "game" project would be a single executible,
		// many annoying warnings which are hard to fix with a dll. Also a static library is faster generally
		// since the compiler knows all symbols at runtime.

		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
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
		PushLayer(new ExampleLayer());	
	}

	~Sandbox() 
	{

	}
};

Dream::Application* Dream::CreateApplication() 
{
	return new Sandbox();
}