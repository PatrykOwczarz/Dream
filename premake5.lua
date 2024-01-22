workspace "Dream"
	architecture "x64"

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

include "Dream/vendor/GLFW"

project "Dream"
	location "Dream"
	kind "SharedLib" -- SharedLib is the same as DLL in premake
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dmpch.h"
	pchsource "Dream/src/dmpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DM_PLATFORM_WINDOWS",
			"DM_BUILD_DLL"
		}

		postbuildcommands { -- This is a workaround to an issue encountered with the COPY
			"copy /B /Y ..\\bin\\" .. outputdir .. "\\Dream\\Dream.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul"
		}

	filter "configurations:Debug"
		defines "DM_DEBUG"
		staticruntime "off"
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		staticruntime "off"
		optimize "On"

	filter "configurations:Dist"
		defines "DM_DIST"
		staticruntime "off"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Dream/src"
	}

	links 
	{
		"Dream"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DM_DEBUG"
		staticruntime "off"
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		staticruntime "off"
		optimize "On"

	filter "configurations:Dist"
		defines "DM_DIST"
		staticruntime "off"
		optimize "On"