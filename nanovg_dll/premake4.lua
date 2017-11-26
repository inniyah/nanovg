
local action = _ACTION or ""

solution "nanovg"
	location ( "build" )
	configurations { "Release", "ReleaseDLL" }
	platforms {"native", "x64", "x32"}

	local homepath = os.getenv("HOME")

	project "nanovg_gl2"
		language "C"
		includedirs { "../nanovg_repository/src" }
		files { "nanovg_dll.c" }
		targetdir("build")
		defines { "NANOVG_GL2_IMPLEMENTATION" }

		configuration "windows"
			files { "nanovg_gl2.def" }
			defines { "_CRT_SECURE_NO_WARNINGS" }
			includedirs { homepath .. "/Libraries/glext/" }
			libdirs { }
			postbuildcommands { "copy nanovg_gl2.dll ..\\..\\demo" }
			links { "opengl32" }

		configuration "macosx"
			postbuildcommands { "cp libnanovg_gl2.dylib ../../demo" }
			linkoptions { "-framework OpenGL" }

		configuration "linux"
			postbuildcommands { "cp libnanovg_gl2.so ../../demo" }
			links { "GL" }

		configuration "Release"
			kind "StaticLib"
			defines { "NDEBUG", "NANOVG_DLL_BUILD" }
			flags { "Optimize", "ExtraWarnings" }

		configuration "ReleaseDLL"
			kind "SharedLib"
			defines { "NDEBUG", "NANOVG_DLL_BUILD" }
			flags { "Optimize", "ExtraWarnings" }

	project "nanovg_gl3"
		language "C"
		includedirs { "../nanovg_repository/src" }
		files { "nanovg_dll.c" }
		targetdir("build")
		defines { "NANOVG_GL3_IMPLEMENTATION" }

		configuration "windows"
			files { "nanovg_gl3.def" }
			defines { "_CRT_SECURE_NO_WARNINGS" }
			includedirs { homepath .. "/Libraries/glext/" }
			libdirs { }
			postbuildcommands { "copy nanovg_gl3.dll ..\\..\\demo" }
			links { "opengl32" }

		configuration "macosx"
			postbuildcommands { "cp libnanovg_gl3.dylib ../../demo" }
			linkoptions { "-framework OpenGL" }

		configuration "linux"
			postbuildcommands { "cp libnanovg_gl3.so ../../demo" }
			links { "GL" }

		configuration "Release"
			kind "StaticLib"
			defines { "NDEBUG", "NANOVG_DLL_BUILD" }
			flags { "Optimize", "ExtraWarnings" }

		configuration "ReleaseDLL"
			kind "SharedLib"
			defines { "NDEBUG", "NANOVG_DLL_BUILD" }
			flags { "Optimize", "ExtraWarnings" }
