workspace "Calculator"
	configurations { "Debug", "DebugASAN", "Release" }
    architecture "x86_64"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:DebugASAN"
		defines { "DEBUG" }
		symbols "On"
		buildoptions { "/fsanitize=address" }
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "On"
		optimize "Full"

project "OpmNum"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/calc/%{cfg.buildcfg}"
	
	files { "src/libopm/**.h", "src/libopm/**.cpp", "src/libopm/**.hpp", "src/libopm/**.inl", "src/libopm/**.natvis" }
	includedirs { "src/libopm", "vendor/antlr/src" }
	links { "Antlr" }

project "Calculator"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/calc/%{cfg.buildcfg}"
	
	files { "src/calc/**.h", "src/calc/**.cpp", "src/calc/**.hpp", "src/calc/**.inl" }
	includedirs { "src/libopm", "vendor" }
	links { "OpmNum", "CppTerminal", "vendor/ftxui/*.lib"}
	
project "CppTerminal"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/cppterm/%{cfg.buildcfg}"
	
	files { "vendor/cpp-terminal/**.cpp" }
	includedirs { "vendor" }
		
project "NTL"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/ntl/%{cfg.buildcfg}"
	
	files { "vendor/ntl/src/**.cpp" }
	includedirs { "vendor/ntl/include" }
	
project "Antlr"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/antlr/%{cfg.buildcfg}"
	
	files { "vendor/antlr/src/**.cpp", "vendor/antlr/src/**.h" }
	includedirs { "vendor/antlr/src" }
	
--[[
project "Testbed"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/testbed/%{cfg.buildcfg}"
	buildoptions { "/openmp" }
	
	files { "src/testbed/**.h", "src/testbed/**.cpp", "src/testbed/**.hpp", "src/testbed/**.inl" }
	includedirs { "src/libopm", "vendor/mahi/include", "vendor/ntl/include" }
	links { "OpmNum", "NTL", "Shcore.lib", "Version.lib", "Pdh.lib", "Winmm.lib" }
	
	filter "configurations:Debug"
		links { "vendor/mahi/Debug/*.lib" }
	
	filter "configurations:Release"
		links { "vendor/mahi/Release/*.lib" } ]]--