workspace "Calculator"
	configurations { "Debug", "Release" }
    architecture "x86_64"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "On"
		optimize "Full"

project "OpmNum"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/calc/%{cfg.buildcfg}"
	
	files { "src/libopm/**.h", "src/libopm/**.cpp", "src/libopm/**.hpp", "src/libopm/**.inl" }
	includedirs { "src/libopm" }

project "Calculator"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/calc/%{cfg.buildcfg}"
	
	files { "src/calc/**.h", "src/calc/**.cpp", "src/calc/**.hpp", "src/calc/**.inl" }
	includedirs { "src/libopm" }
	links { "OpmNum" }
		
project "NTL"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/ntl/%{cfg.buildcfg}"
	
	files { "vendor/ntl/src/**.cpp" }
	includedirs { "vendor/ntl/include" }
	
project "Testbed"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/testbed/%{cfg.buildcfg}"
	
	files { "src/testbed/**.h", "src/testbed/**.cpp", "src/testbed/**.hpp", "src/testbed/**.inl" }
	includedirs { "src/libopm", "vendor/mahi/include", "vendor/ntl/include" }
	links { "OpmNum", "NTL", "Shcore.lib", "Version.lib", "Pdh.lib", "Winmm.lib" }
	
	filter "configurations:Debug"
		links { "vendor/mahi/Debug/*.lib" }
	
	filter "configurations:Release"
		links { "vendor/mahi/Release/*.lib" }