workspace "Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-x64"

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDir["GLAD"] = "Engine/vendor/GLAD/include"

include "Engine/vendor/GLFW"
include "Engine/vendor/GLAD"
project "Engine"
	
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ENPH.h"
	pchsource "Engine/src/ENPH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/Vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}

	links
	{
		"GLAD",
		"GLFW",
		"opengl32.lib"
	}

	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"


	defines
	{
		"EN_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Tester"
	}
	filter "configurations:Debug"
		defines "EN_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "EN_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		buildoptions "/MD"
		optimize "On"

project "Tester"
	location "Tester"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Engine/Vendor/spdlog/include",
		"Engine/src"
	}

	links
	{
		"Engine"
	}

	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	defines
	{
	}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "EN_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		buildoptions "/MD"
		optimize "On"