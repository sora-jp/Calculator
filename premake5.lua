workspace "Calculator"
	configurations { "Debug", "Release" }

project "Calculator"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	
	files { "src/**.h", "src/**.cpp", "src/**.hpp", "src/**.inl" }
	includedirs { "src/libopm" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "On"
		optimize "Full"