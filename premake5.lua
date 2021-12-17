-- premake5.lua
-- �����������
workspace "HelloEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

-- ����: Debug-Windows-x64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- �����ĵ������� 
IncludeDirs_3rdParty = {}
IncludeDirs_3rdParty["GLFW"] = "HelloEngine/3rdParty/GLFW/include"
IncludeDirs_3rdParty["Glad"] = "HelloEngine/3rdParty/Glad/include"
IncludeDirs_3rdParty["ImGui"] = "HelloEngine/3rdParty/imgui"

include "HelloEngine/3rdParty/GLFW"
include "HelloEngine/3rdParty/Glad"
include "HelloEngine/3rdParty/imgui"

-- ��Ŀ���� ------- ������Ŀ
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
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/3rdParty/spdlog/include",
		"%{IncludeDirs_3rdParty.GLFW}",
		"%{IncludeDirs_3rdParty.Glad}",
		"%{IncludeDirs_3rdParty.ImGui}"
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

	
-- ��Ŀ���� ------- Sandbox��Ŀ
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
		"HelloEngine/3rdParty/spdlog/include"
		
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
	