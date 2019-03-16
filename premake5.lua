workspace "Sgl"
	architecture "x64"
	startproject "test"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"]   = "deps/GLFW/include"
IncludeDir["Glad"]   = "deps/Glad/include"
IncludeDir["glm"]    = "deps/glm"
IncludeDir["spdlog"] = "deps/spdlog/include"

include "deps/GLFW"
include "deps/Glad"

project "Sgl"
	location "src"
	kind "StaticLib"
	language "C++"
	--staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/**.h",
		"src/**.cpp",
		"deps/stb_image/stb_image.cpp",
		"deps/glm/glm/**.hpp",
		"deps/glm/glm/**.inl",
	}

	includedirs
	{
		"include",
		"deps",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++11"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/test/\"")
		}

		excludes { "src/Platform/GLES2/**.cpp" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

project "test"
	location "test"
	kind "ConsoleApp"
	language "C++"
	--staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"include",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Sgl"
	}

	filter "system:windows"
		cppdialect "C++11"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		debugdir ".."

	filter "configurations:Release"
		runtime "Release"
		optimize "On"