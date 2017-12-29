function addproject(name)
	project (name)
		kind "ConsoleApp"
		language "C++"
		
		files {
			path.join("example", name, "**.cpp"),
		}
		
		includedirs {
			"./include",
		}
end

workspace "literally"
	configurations { "Debug", "Release" }
	platforms { "Win32", "Win64" }

	addproject("io")
	addproject("library")
	addproject("memory")


workspace "*"
	location "./build"
	objdir "%{wks.location}/obj"
	targetdir "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	buildlog "%{wks.location}/obj/%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}/%{prj.name}.log"

	buildoptions {
		"/std:c++latest"
	}
	
	largeaddressaware "on"
	
	filter "platforms:*32"
		architecture "x86"
	
	filter "platforms:*64"
		architecture "x86_64"
	
	filter "platforms:Win*"
		system "windows"
		defines { "_WINDOWS" }
	
	filter {}

	warnings "Extra"
	
	flags {
		"StaticRuntime",
		"NoIncrementalLink",
		"NoMinimalRebuild",
		"MultiProcessorCompile",
		"No64BitChecks",
		"UndefinedIdentifiers",
	}
	
	editandcontinue "Off"
	symbols "On"

	configuration "Release*"
		defines { "NDEBUG" }
		optimize "On"
		flags {
			"FatalCompileWarnings",
			"FatalLinkWarnings",
		}

	configuration "Debug*"
		defines { "DEBUG", "_DEBUG" }
		optimize "Debug"
