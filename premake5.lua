-- premake5.lua
-- 解决方案设置
workspace "HelloEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

-- 例子: Debug-Windows-x64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- 包含的第三方库 
IncludeDirs_3rdParty = {}
IncludeDirs_3rdParty["spdlog"] = "HelloEngine/3rdParty/spdlog/include"
IncludeDirs_3rdParty["GLFW"] = "HelloEngine/3rdParty/GLFW/include"
IncludeDirs_3rdParty["Glad"] = "HelloEngine/3rdParty/Glad/include"
IncludeDirs_3rdParty["ImGui"] = "HelloEngine/3rdParty/imgui"
IncludeDirs_3rdParty["glm"] = "HelloEngine/3rdParty/glm"

include "HelloEngine/3rdParty/GLFW"
include "HelloEngine/3rdParty/Glad"
include "HelloEngine/3rdParty/imgui"

-- 项目设置 ------- 引擎项目
project "HelloEngine"
	location "HelloEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "hepch.h"
	pchsource "%{prj.name}/src/hepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/3rdParty/glm/glm/**.hpp",
		"%{prj.name}/3rdParty/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDirs_3rdParty.spdlog}",
		"%{IncludeDirs_3rdParty.GLFW}",
		"%{IncludeDirs_3rdParty.Glad}",
		"%{IncludeDirs_3rdParty.ImGui}",
		"%{IncludeDirs_3rdParty.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"	
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"HE_PLATFORM_WINDOWS",
			"HE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../bin/"..outputdir.."/Sandbox/\"")
	}

	filter "configurations:Debug"
		defines "HE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HE_DIST"
		runtime "Release"
		optimize "On"

	
-- 项目设置 ------- Sandbox项目
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"HelloEngine/src",
		"%{IncludeDirs_3rdParty.spdlog}",
		"%{IncludeDirs_3rdParty.glm}",
		"HelloEngine/3rdParty"
	}

	links
	{
		"HelloEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HE_DIST"
		runtime "Release"
		optimize "On"
	