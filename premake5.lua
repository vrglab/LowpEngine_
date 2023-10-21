function determine_os()
    if os.ishost("windows") then
        return "windows"
    elseif os.ishost("linux") then
        return "linux"
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


-- C# projects related to the engine
group "C#/Engine related"
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
		"AssetsSystem",
		"GlobalUtilities",
		"Packages/c#/log4net.2.0.15/lib/netstandard2.0/log4net.dll"
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
			
project "TestGame"
		location "TestGame"
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
			"LowpEngine"
		}
	
		filter "configurations:Debug"
			symbols "On"
	
		filter "configurations:Release"
			optimize "On"

-- Engines Console based tools
group "C#/Console Apps"
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

-- C++ core engine and its other helpers
group "C++"
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
		links 
		{
			"d3d12",
			"dxgi",
			"D3DCompiler"
		}
		libdirs
		{
			"Packages/c++/libs/windows"
		}
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
		"Packages/c++/includes",
		"%{prj.name}",
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine",
		"EngineCommons",
		"Scripting"
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
		"tinyexr",
		"volk",
		"zlib",
		"glew32",
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine",
		"EngineCommons",
		"mono-2.0-sgen",
		"Scripting"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines {"DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

project "EngineCommons"
	location "EngineCommons"
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
		pchheader "lpcopch.h"
		cppdialect "C++latest"
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lpcopch.h"
	end

	pchsource "%{prj.name}/lpcopch.cpp"

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
		"Packages/c++/includes",
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
		"tinyexr",
		"volk",
		"zlib",
		"glew32"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines {"DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

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
		"Packages/c++/includes",
		"%{prj.name}",
		"Engine",
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine",
		"EngineCommons",
		"Scripting"
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
		"tinyexr",
		"volk",
		"zlib",
		"OpenAL32",
		"fmod",
		"fmodstudio",
		"Engine",
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine",
		"EngineCommons"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines {"DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

-- C++ Subsystems that are used in the engine
group "C++/Subsystem"
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
		"%{prj.name}",
		"EngineCommons",
		"Packages/c++/includes"
	}
	
	links
	{
		"OpenAL32",
		"fmod",
		"fmodstudio",
		"EngineCommons"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++20"
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
		"%{prj.name}",
		"EngineCommons",
		"Packages/c++/includes"
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
		"tinyexr",
		"volk",
		"zlib",
		"ode_double",
		"box2d",
		"EngineCommons"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++20"
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
		links 
		{
			"d3d12",
			"dxgi",
			"D3DCompiler"
		}
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
		"%{prj.name}",
		"EngineCommons"
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
		"tinyexr",
		"volk",
		"zlib",
		"EngineCommons"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines {"DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

project "Scripting"
	location "Scripting"
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
		pchheader "lpscpch.h"
		cppdialect "C++latest"
		links 
		{
			"d3d12",
			"dxgi"
		}
		libdirs
		{
			"Packages/c++/libs/windows"
		}
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lpscpch.h"
	end

	pchsource "%{prj.name}/lpscpch.cpp"

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
		"Packages/c++/includes",
		"%{prj.name}",
		"SoundSystem",
		"PhysicsEngine",
		"RenderingEngine",
		"EngineCommons"
	}
	
	links
	{
		"EngineCommons",
		"mono-2.0-sgen"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines { "DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}

project "SceneEngine"
	location "SceneEngine"
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
		pchheader "lpsmpch.h"
		cppdialect "C++latest"
		libdirs
		{
			"Packages/c++/libs/windows"
		}
	elseif os.target() == "linux" then
		pchheader "%{prj.name}/lpsmpch.h"
	end

	pchsource "%{prj.name}/lpsmpch.cpp"

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
		"Packages/c++/includes",
		"%{prj.name}",
		"EngineCommons"
	}
	
	links
	{
		"EngineCommons"
	}

	vpaths {
		["Headers/*"] = { "**.h", "**.hpp" },
		["Sources/*"] = {"**.c", "**.cpp"}
	}


	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines { "DEBUG"}

	filter "configurations:Release"
		optimize "On"
		defines {"RELEASE"}