workspace "Dream"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.sustem}-%{cfg.architecture}"

-- Include directories relative to solution directory (root folder)
IncludeDir = {}
IncludeDir["GLFW"] = "Dream/vendor/GLFW/include"
IncludeDir["Glad"] = "Dream/vendor/Glad/include"
IncludeDir["ImGui"] = "Dream/vendor/imgui"
IncludeDir["glm"] = "Dream/vendor/glm"

include "Dream/vendor/GLFW"
include "Dream/vendor/Glad"
include "Dream/vendor/imgui"

group "Dependencies"
	include "Dream/vendor/GLFW"
	include "Dream/vendor/Glad"
	include "Dream/vendor/imgui"

group ""

project "Dream"
	location "Dream"
	kind "SharedLib" -- SharedLib is the same as DLL in premake
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dmpch.h"
	pchsource "Dream/src/dmpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"DM_PLATFORM_WINDOWS",
			"DM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands { -- This is a workaround to an issue encountered with the COPY
			"copy /B /Y ..\\bin\\" .. outputdir .. "\\Dream\\Dream.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul"
		}

	filter "configurations:Debug"
		defines "DM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DM_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Dream/vendor/spdlog/include",
		"Dream/src",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"Dream"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"DM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DM_DIST"
		runtime "Release"
		optimize "On"