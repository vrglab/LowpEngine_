function determine_os()
    if os.ishost("windows") then
        return "Windows"
    elseif os.ishost("linux") then
        return "Linux"
    elseif os.ishost("macosx") then
        return "macOS"
    else
        return "Unknown"
    end
end

-- Function to determine the current architecture
function determine_architecture()
    if os.is64bit() then
        return "x64"
    else
        return "x86"
    end
end


workspace "LowpEngine"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release"
	}
	platforms { "x86", "x64", "ARM", "ARM64" }
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	vcpkg_arg_dir = determine_architecture().."-"..determine_os();

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	if os.target() == "windows" then
		pchheader "lppch.h"
		cppdialect "C++latest"
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lppch.h"
	end

	pchsource "%{prj.name}/lppch.cpp"

	files 
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**/**.h",
		"%{prj.name}/**/**.cpp"
	}

	libdirs
	{
		"Programs/vcpkg/installed/"..vcpkg_arg_dir.."/lib"
	}

	includedirs
	{
		"Programs/vcpkg/installed/"..vcpkg_arg_dir.."/include",
		"%{prj.name}"
	}
	
	links
	{
		"assimp-vc143-mt",
		"bgfx",
		"bimg",
		"bimg_decode",
		"bimg_encode",
		"bx",
		"CompilerSpirV",
		"draco",
		"GlU32",
		"kubazip",
		"miniz",
		"minizip",
		"poly2tri",
		"polyclipping",
		"pugixml",
		"SDL2",
		"ShaderAST",
		"ShaderWriter",
		"squish",
		"tinyexr",
		"volk",
		"zlib",
		"SoundSystem"
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

	filter "configurations:Release"
		optimize "On"

project "Engine.UI"
		location "Engine_UI"
		kind "SharedLib"
		language "C++"
	
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	
		if os.target() == "windows" then
			pchheader "lpuipch.h"
			cppdialect "C++latest"
		elseif os.target() == "linux" then
			pchheader "%{prj.location}/lpuipch.h"
		end
	
		pchsource "%{prj.location}/lpuipch.cpp"
	
		libdirs
		{
			"Programs/vcpkg/installed/"..vcpkg_arg_dir.."/lib"
		}
	
		includedirs
		{
			"Programs/vcpkg/installed/"..vcpkg_arg_dir.."/include",
			"%{prj.name}"
		}
		
		links
		{
			"assimp-vc143-mt",
			"bgfx",
			"bimg",
			"bimg_decode",
			"bimg_encode",
			"bx",
			"CompilerSpirV",
			"draco",
			"GlU32",
			"kubazip",
			"miniz",
			"minizip",
			"OpenGL32",
			"poly2tri",
			"polyclipping",
			"pugixml",
			"SDL2",
			"ShaderAST",
			"ShaderWriter",
			"squish",
			"tinyexr",
			"volk",
			"zlib"
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
	
		filter "configurations:Release"
			optimize "On"

project "SoundSystem"
	location "SoundSystem"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	if os.target() == "windows" then
		pchheader "lppch.h"
		cppdialect "C++latest"
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lppch.h"
	end

	pchsource "%{prj.name}/lppch.cpp"

	files 
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**/**.h",
		"%{prj.name}/**/**.cpp"
	}

	libdirs
	{
		"Programs/vcpkg/installed/"..vcpkg_arg_dir.."/lib"
	}

	includedirs
	{
		"Programs/vcpkg/installed/"..vcpkg_arg_dir.."/include",
		"%{prj.name}"
	}
	
	links
	{
		"OpenAL32",
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
