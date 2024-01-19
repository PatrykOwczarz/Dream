#pragma once

#ifdef DM_PLATFORM_WINDOWS

extern Dream::Application* Dream::CreateApplication();

int main(int argc, char** argv) 
{
	Dream::Log::Init();
	DM_CORE_WARN("Initialized Log!");

	auto app = Dream::CreateApplication();
	app->Run();
	delete app;
}

#endif