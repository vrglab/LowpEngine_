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
	toolset "v143"
	buildoptions
	{
		"/Zc:__cplusplus"
	}

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
		"%{prj.name}",
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine"
	}
	
	links
	{
		"assimp-vc143-mt",
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
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine"
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
		defines {"DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

project "Engine.UI"
		location "Engine_UI"
		kind "SharedLib"
		language "C++"
		toolset "v143"
		buildoptions
		{
			"/Zc:__cplusplus"
		}
	
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
			"%{prj.location}"
		}
		
		links
		{
			"assimp-vc143-mt",
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

		files 
		{
			"%{prj.location}/**.h",
			"%{prj.location}/**.cpp",
			"%{prj.location}/**/**.h",
			"%{prj.location}/**/**.cpp"
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
			defines {"DEBUG"}

	    filter "configurations:Release"
			optimize "On"
			defines {"RELEASE"}

project "SoundSystem"
	location "SoundSystem"
	kind "StaticLib"
	language "C++"
	toolset "v143"
	buildoptions
	{
		"/Zc:__cplusplus"
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	if os.target() == "windows" then
		pchheader "lpsspch.h"
		cppdialect "C++latest"
		libdirs
		{
			"Packages/c++/libs/windows"
		}
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lpsspch.h"
	end

	pchsource "%{prj.name}/lpsspch.cpp"

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
		defines { "DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

project "PhysicsEngine"
	location "PhysicsEngine"
	kind "StaticLib"
	language "C++"
	toolset "v143"
	buildoptions
	{
		"/Zc:__cplusplus"
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	if os.target() == "windows" then
		pchheader "lpphpch.h"
		cppdialect "C++latest"
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lpphpch.h"
	end

	pchsource "%{prj.name}/lpphpch.cpp"

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
		"ode_double",
		"box2d"
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
		defines {"DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

project "RenderingEngine"
	location "RenderingEngine"
	kind "StaticLib"
	language "C++"
	toolset "v143"
	buildoptions
	{
		"/Zc:__cplusplus"
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	if os.target() == "windows" then
		pchheader "lprdpch.h"
		cppdialect "C++latest"
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lprdpch.h"
	end

	pchsource "%{prj.name}/lprdpch.cpp"

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
		defines {"DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

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
			"GlobalUtilities",
			"Packages/c#/MessagePack.2.5.129/lib/netstandard2.0/MessagePack.dll",
			"Packages/c#/MessagePack.Annotations.2.5.129/lib/netstandard2.0/MessagePack.Annotations.dll",
			"Packages/c#/System.Buffers.4.5.1/lib/netstandard2.0/System.Buffers.dll",
			"Packages/c#/System.Memory.4.5.5/lib/netstandard2.0/System.Memory.dll",
			"Packages/c#/System.Numerics.Vectors.4.5.0/lib/netstandard2.0/System.Numerics.Vectors.dll",
			"Packages/c#/System.Runtime.CompilerServices.Unsafe.6.0.0/lib/netstandard2.0/System.Runtime.CompilerServices.Unsafe.dll",
			"Packages/c#/Microsoft.NET.StringTools.17.6.3/lib/netstandard2.0/Microsoft.NET.StringTools.dll",
			"Packages/c#/System.Collections.Immutable.7.0.0/lib/netstandard2.0/System.Collections.Immutable.dll"
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
		"Engine.UI",
		"AssetsSystem",
		"GlobalUtilities",
		"Packages/c#/log4net.2.0.15/lib/netstandard2.0/log4net.dll"
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
			"GlobalUtilities",
			"Packages/c#/MessagePack.2.5.129/lib/netstandard2.0/MessagePack.dll",
			"Packages/c#/MessagePack.Annotations.2.5.129/lib/netstandard2.0/MessagePack.Annotations.dll",
			"Packages/c#/System.Buffers.4.5.1/lib/netstandard2.0/System.Buffers.dll",
			"Packages/c#/System.Memory.4.5.5/lib/netstandard2.0/System.Memory.dll",
			"Packages/c#/System.Numerics.Vectors.4.5.0/lib/netstandard2.0/System.Numerics.Vectors.dll",
			"Packages/c#/System.Runtime.CompilerServices.Unsafe.6.0.0/lib/netstandard2.0/System.Runtime.CompilerServices.Unsafe.dll",
			"Packages/c#/Microsoft.NET.StringTools.17.6.3/lib/netstandard2.0/Microsoft.NET.StringTools.dll",
			"Packages/c#/System.Collections.Immutable.7.0.0/lib/netstandard2.0/System.Collections.Immutable.dll"
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
			"System"
		}
	
		filter "configurations:Debug"
			symbols "On"
	
		filter "configurations:Release"
			optimize "On"

project "Launcher"
	location "Launcher"
	kind "ConsoleApp"
	language "C++"
	toolset "v143"
	buildoptions
	{
		"/Zc:__cplusplus"
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")



	if os.target() == "windows" then
		pchheader "lplupch.h"
		cppdialect "C++latest"
		libdirs
		{
			"Packages/c++/libs/windows"
		}
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lplupch.h"
	end

	pchsource "%{prj.name}/lplupch.cpp"

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
		"%{prj.name}",
		"Engine",
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine"
	}
	
	links
	{
		"assimp-vc143-mt",
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
		"OpenAL32",
		"fmod",
		"fmodstudio",
		"Engine",
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine"
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
		defines { "DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}
			
project "TestGame"
		location "TestGame"
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
			"LowpEngine"
		}
	
		filter "configurations:Debug"
			symbols "On"
	
		filter "configurations:Release"
			optimize "On"
