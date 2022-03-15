
local action = _ACTION or ""

solution "nanovg-nanort"
	location ( "build" )
	configurations { "Debug", "Release" }
	platforms {"native", "x64", "x32"}
	
   	project "nanovg"
		language "C"
		kind "StaticLib"
		includedirs { "src" }
		files { "src/*.c" }
		targetdir("build")
		defines { "_CRT_SECURE_NO_WARNINGS" } --,"FONS_USE_FREETYPE" } Uncomment to compile with FreeType support
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols"}

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize"}


	project "example_rt"
		kind "ConsoleApp"
		language "C++"
		files { "example/example_rt.cc", "example/demo.c" }
		includedirs { "src", "example" }
		targetdir("build")
		links { "nanovg" }

		configuration { "windows" }
			 links { "gdi32", "winmm", "user32", "kernel32" }
			 defines { "_CRT_SECURE_NO_WARNINGS" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols"}

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize"}
