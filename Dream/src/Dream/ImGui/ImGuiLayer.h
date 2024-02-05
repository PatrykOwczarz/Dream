#pragma once
#include "Dream/Layer.h";

#include "Dream/Events/MouseEvent.h"
#include "Dream/Events/ApplicationEvent.h"
#include "Dream/Events/KeyEvent.h"

namespace Dream {

	class DREAM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}
