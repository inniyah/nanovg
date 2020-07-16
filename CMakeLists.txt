CMAKE_MINIMUM_REQUIRED(VERSION 3.13 FATAL_ERROR)
PROJECT("nanovg")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Build Library

#~ ADD_LIBRARY(nanovg OBJECT src/nanovg.c)
#~ TARGET_INCLUDE_DIRECTORIES(nanovg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#~ TARGET_COMPILE_DEFINITIONS(nanovg PRIVATE ${NANOVG_DEFINES})
#~ SET_PROPERTY(TARGET nanovg PROPERTY POSITION_INDEPENDENT_CODE ON)

#~ ADD_LIBRARY(nanovg_gl3 OBJECT src/nanovg_gl.c src/nanovg_gl_utils.c)
#~ SET_TARGET_PROPERTIES(nanovg_gl3 PROPERTIES VERSION 0.0.20200320 SOVERSION 0)
#~ TARGET_INCLUDE_DIRECTORIES(nanovg_gl3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#~ TARGET_COMPILE_DEFINITIONS(nanovg_gl3 PRIVATE NANOVG_GLEW NANOVG_GL3)
#~ SET_PROPERTY(TARGET nanovg_gl3 PROPERTY POSITION_INDEPENDENT_CODE ON)

#~ ADD_LIBRARY(nanovg_gles3 OBJECT src/nanovg_gl.c src/nanovg_gl_utils.c)
#~ SET_TARGET_PROPERTIES(nanovg_gles3 PROPERTIES VERSION 0.0.20200320 SOVERSION 0)
#~ TARGET_INCLUDE_DIRECTORIES(nanovg_gles3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#~ TARGET_COMPILE_DEFINITIONS(nanovg_gles3 PRIVATE NANOVG_GLEW NANOVG_GLES3)
#~ SET_PROPERTY(TARGET nanovg_gles3 PROPERTY POSITION_INDEPENDENT_CODE ON)

#~ ADD_LIBRARY(nanovg_so SHARED $<TARGET_OBJECTS:nanovg>)
#~ SET_TARGET_PROPERTIES(nanovg_so PROPERTIES VERSION 0.0.20200320 SOVERSION 0)
#~ SET_TARGET_PROPERTIES(nanovg_so PROPERTIES OUTPUT_NAME nanovg)
#~ TARGET_LINK_LIBRARIES(nanovg_so nanovg nanovg_gl3 GLEW EGL GL m)

#~ ADD_LIBRARY(nanovg_a STATIC $<TARGET_OBJECTS:nanovg>)
#~ SET_TARGET_PROPERTIES(nanovg_a PROPERTIES OUTPUT_NAME nanovg)
#~ TARGET_LINK_LIBRARIES(nanovg_a nanovg nanovg_gl3 GLEW EGL GL m)

#~ INSTALL(TARGETS nanovg_so
#~         LIBRARY DESTINATION lib
#~         ARCHIVE DESTINATION lib
#~         RUNTIME DESTINATION bin)

#~ INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/
#~         DESTINATION include/nanovg
#~         FILES_MATCHING PATTERN "*.h*")


# Build Examples

ADD_EXECUTABLE(example_gl2 example/example_gl2.c example/demo.c example/perf.c src/nanovg.c src/nanovg_gl.c)
TARGET_LINK_LIBRARIES(example_gl2 GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_gl2 PRIVATE NANOVG_GLEW NANOVG_GL2)

ADD_EXECUTABLE(example_gl3 example/example_gl3.c example/demo.c example/perf.c src/nanovg.c src/nanovg_gl.c)
TARGET_LINK_LIBRARIES(example_gl3 GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_gl3 PRIVATE NANOVG_GLEW NANOVG_GL3)

ADD_EXECUTABLE(example_gles2 example/example_gles2.c example/demo.c example/perf.c src/nanovg.c src/nanovg_gl.c)
TARGET_LINK_LIBRARIES(example_gles2 GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_gles2 PRIVATE NANOVG_GLES2)

ADD_EXECUTABLE(example_gles3 example/example_gles3.c example/demo.c example/perf.c src/nanovg.c src/nanovg_gl.c)
TARGET_LINK_LIBRARIES(example_gles3 GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_gles3 PRIVATE NANOVG_GLES3)

ADD_EXECUTABLE(example_fbo example/example_fbo.c example/demo.c example/perf.c src/nanovg.c src/nanovg_gl.c src/nanovg_gl_utils.c)
TARGET_LINK_LIBRARIES(example_fbo GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_fbo PRIVATE NANOVG_GLEW NANOVG_GL3)

ADD_EXECUTABLE(example_svg1 example/example_svg1.c src/nanovg.c)
TARGET_LINK_LIBRARIES(example_svg1 GLEW EGL GL glfw m)

ADD_EXECUTABLE(example_svg2 example/example_svg2.c src/nanovg.c)
TARGET_LINK_LIBRARIES(example_svg2 GLEW EGL GL glfw m)
