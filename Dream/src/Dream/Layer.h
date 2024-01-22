#pragma once

#include "Dream/Core.h"
#include "Dream/Events/Event.h"

namespace Dream {

	class DREAM_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}