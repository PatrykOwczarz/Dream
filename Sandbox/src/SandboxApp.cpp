#include <Dream.h>

#include "imgui/imgui.h"

#include "Dream/Renderer/Shader.h"
#include "Dream/Renderer/Buffer.h"
#include "Dream/Renderer/VertexArray.h"
#include "Dream/Renderer/Renderer.h"

class ExampleLayer : public Dream::Layer
{
private:
	std::shared_ptr<Dream::Shader> m_Shader;
	std::shared_ptr<Dream::VertexArray> m_VertexArray;

public:
	ExampleLayer()
		: Layer("Example")
	{
		// ------- Rendering triangle --------------------
		m_VertexArray.reset(Dream::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f

		};

		std::shared_ptr<Dream::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Dream::VertexBuffer::Create(vertices, sizeof(vertices)));

		Dream::BufferLayout layout = {
			{ Dream::ShaderDataType::Float3, "a_Position" },
			{ Dream::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// This draws a square by drawing 2 triangles made of indices 0, 1, 2 and 0, 3 ,1 with anti-clockwise winding.
		// unsigned int indices[6] = { 0 , 1 , 2 , 0 , 3, 1};

		// code for 1 triangle
		uint32_t indices[3] = { 0 , 1 , 2 };
		std::shared_ptr<Dream::IndexBuffer> indexBuffer;
		indexBuffer.reset(Dream::IndexBuffer::Create(indices, std::size(indices)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;		
			layout(location = 1) in vec4 a_Color;			

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;			

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Dream::Shader(vertexSrc, fragmentSrc));
		// ------- Rendering triangle --------------------

	}

	void OnUpdate() override
	{
		//DM_INFO("ExampleLayer::Update");

		// ------- Rendering triangle --------------------
		Dream::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Dream::RenderCommand::Clear();

		Dream::Renderer::BeginScene();

		m_Shader->Bind();
		Dream::Renderer::Submit(m_VertexArray);

		Dream::Renderer::EndScene();
		// ------- Rendering triangle --------------------

		if (Dream::Input::IsKeyPressed(DM_KEY_TAB))
			DM_TRACE("Tab key is pressed (poll)!");
		
	}

	virtual void OnImGuiRender() override
	{
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