workspace "Engine"
	architecture "x64"
	startproject "Tester"
	
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
IncludeDir["ImGUI"] = "Engine/vendor/ImGUI"
IncludeDir["glm"] = "Engine/vendor/glm"

group "Dependencies"
include "Engine/vendor/GLFW"
include "Engine/vendor/GLAD"
include "Engine/vendor/ImGUI"
group ""

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

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/Vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"ImGUI",
		"GLAD",
		"GLFW",
		"opengl32.lib"
	}

	cppdialect "C++17"
	staticruntime "Off"
	systemversion "latest"


	defines
	{
		"EN_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Tester/\""
	}

	buildoptions "/wd4251"
	
	filter "configurations:Debug"
		defines "EN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "EN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		runtime "Release"
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
		"Engine/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Engine"
	}

	cppdialect "C++17"
	staticruntime "Off"
	systemversion "latest"

	defines
	{

	}

	buildoptions "/wd4251"

	filter "configurations:Debug"
		defines "EN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "EN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		runtime "Release"
		optimize "On"