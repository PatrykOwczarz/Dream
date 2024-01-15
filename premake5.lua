workspace "Dream"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.sustem}-%{cfg.architecture}"

project "Dream"
	location "Dream"
	kind "SharedLib" -- SharedLib is the same as DLL in premake
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
		"%{prj.name}/vendor/spdlog/include"
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
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DM_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DM_DIST"
		optimize "On"