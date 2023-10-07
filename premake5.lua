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


	if os.target() == "windows" then
		pchheader "lppch.h"
		libdirs
		{
			"Packages/c++/libs"
		}
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lppch.h"
		libdirs
		{
			"../Packages/c++/libs"
		}
	end

	pchsource "%{prj.name}/lppch.cpp"

	files 
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**/**.h",
		"%{prj.name}/**/**.cpp"
	}

	includedirs
	{
		"Packages/c++/includes/"
	}
	
	links
	{
		"SDL2",
		"HLSL",
		"OpenAL32",
		"shaderc",
		"SPIRV",
		"vulkan-1",
		"fmod",
		"fmodstudio",
		"assimp-vc143-mt"
	}
	

	vpaths {
		["Headers"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		links
		{
			"bgfxDebug",
			"libs/bimgDebug",
			"bxDebug"
		}

	filter "configurations:Release"
		optimize "On"
		links
		{
			"bgfxRelease",
			"bimgRelease",
			"bxRelease"
		}
		
project "LowpEngine"
	location "LowpEngine"
	kind "SharedLib"
	language "C#"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/**.cs",
		"%{prj.name}/**/**.cs"
	}
	
	links
	{
		"Engine",
		"Packages/c#/log4net/net20/log4net.dll"
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
		"%{prj.name}/**.cs",
		"%{prj.name}/**/**.cs"
	}

	links
	{
		"LowpEngine",
		"Packages/c#/log4net/net20/log4net.dll"
	}

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"