workspace "LowpEngine"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release"
	}
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lppch.h"
	pchsource "%{prj.name}/lppch.cpp"

	files 
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"Packages/c++/includes/"
	}
	
	links
	{
		"Packages/c++/libs/SDL2.lib",
		"Packages/c++/libs/HLSL.lib",
		"Packages/c++/libs/OpenAL32.lib",
		"Packages/c++/libs/shaderc.lib",
		"Packages/c++/libs/SPIRV.lib",
		"Packages/c++/libs/vulkan-1.lib",
		"Packages/c++/libs/fmod.lib",
		"Packages/c++/libs/fmodstudio.lib",
		"Packages/c++/libs/opus.dll",
		"Packages/c++/libs/libfsbvorbis64.dll",
		"Packages/c++/libs/fsbank.dll"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"
		
project "LowpEngine"
	location "LowpEngine"
	kind "SharedLib"
	language "C#"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/**.cs"
	}
	
	links
	{
		"Engine"
	}

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"	

project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C#"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/**.cs"
	}

	links
	{
		"LowpEngine"
	}

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

	filter "configurations:Dist"
		symbols "On"