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
			"Packages/c++/libs/windows"
		}
		links
		{
			"SDL2",
			"vulkan-1",
			"assimp-vc143-mt"
		}
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lppch.h"
		libdirs
		{
			"/Packages/c++/libs/linux"
		}
		links
		{
			"SDL2-2.0.so.0",
			"vulkan",
			"assimp"
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
		"Packages/c++/includes/",
		"%{prj.name}"
	}
	
	links
	{
		"HLSL",
		"OpenAL32",
		"shaderc",
		"SPIRV",
		"fmod",
		"fmodstudio"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
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
			"bimgDebug",
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

project "Engine.UI"
		location "Engine_UI"
		kind "SharedLib"
		language "C++"
	
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	
		if os.target() == "windows" then
			pchheader "lpuipch.h"
			libdirs
			{
				"Packages/c++/libs/windows"
			}
		elseif os.target() == "linux" then
			pchheader "%{prj.location}/lpuipch.h"
			libdirs
			{
				"/Packages/c++/libs/linux"
			}
		end
	
		pchsource "%{prj.location}/lpuipch.cpp"
	
		files 
		{
			"%{prj.location}/**.h",
			"%{prj.location}/**.cpp",
			"%{prj.location}/**/**.h",
			"%{prj.location}/**/**.cpp"
		}
	
		includedirs
		{
			"Packages/c++/includes/"
		}
		
		links
		{
			"Engine"
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
	
		filter "configurations:Release"
			optimize "On"

project "AssetsSystem"
		location "AssetsSystem"
		kind "SharedLib"
		language "C#"
		csversion ("11")
	
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
		files 
		{
			"%{prj.name}/**.cs",
			"%{prj.name}/**/**.cs"
		}
		links
		{
			"GlobalUtilities"
		}
	
		filter "configurations:Debug"
			symbols "On"
	
		filter "configurations:Release"
			optimize "On"		

project "LowpEngine"
	location "LowpEngine"
	kind "SharedLib"
	language "C#"
	csversion ("11")

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
		"Engine.UI",
		"AssetsSystem",
		"GlobalUtilities",
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
	csversion ("11")

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
		"GlobalUtilities",
		"AssetsTool"
	}

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

project "ConsoleAppEngine"
		location "ConsoleAppEngine"
		kind "SharedLib"
		language "C#"
		csversion ("11")
	
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
		files 
		{
			"%{prj.name}/**.cs",
			"%{prj.name}/**/**.cs"
		}
		links
		{
			"GlobalUtilities"
		}
	
		filter "configurations:Debug"
			symbols "On"
	
		filter "configurations:Release"
			optimize "On"

project "AssetsTool"
		location "AssetsTool"
		kind "ConsoleApp"
		language "C#"
		csversion ("11")
	
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
			"ConsoleAppEngine",
			"AssetsSystem",
			"GlobalUtilities"
		}
	
		filter "configurations:Debug"
			symbols "On"
	
		filter "configurations:Release"
			optimize "On"

project "GlobalUtilities"
		location "GlobalUtilities"
		kind "SharedLib"
		language "C#"
		csversion ("11")
	
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
		files 
		{
			"%{prj.name}/**.cs",
			"%{prj.name}/**/**.cs"
		}
	
		links
		{

		}
	
		filter "configurations:Debug"
			symbols "On"
	
		filter "configurations:Release"
			optimize "On"