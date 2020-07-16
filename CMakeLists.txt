CMAKE_MINIMUM_REQUIRED(VERSION 3.13 FATAL_ERROR)
PROJECT("nanovg")

# Build Library

SET(NANOVG_SOURCE src/nanovg.c)

ADD_LIBRARY(nanovg SHARED ${NANOVG_SOURCE})
SET_TARGET_PROPERTIES(nanovg PROPERTIES VERSION 0.0.20200320 SOVERSION 0)
TARGET_INCLUDE_DIRECTORIES(nanovg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
TARGET_LINK_LIBRARIES(nanovg m)

ADD_LIBRARY(nanovg_static STATIC ${NANOVG_SOURCE})
SET_TARGET_PROPERTIES(nanovg_static PROPERTIES OUTPUT_NAME nanovg)
TARGET_INCLUDE_DIRECTORIES(nanovg_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
TARGET_LINK_LIBRARIES(nanovg_static m)

INSTALL(TARGETS nanovg nanovg_static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/
        DESTINATION include/nanovg
        FILES_MATCHING PATTERN "*.h*")


# Build Examples

ADD_EXECUTABLE(example_gl2 example/example_gl2.c example/demo.c example/perf.c)
TARGET_LINK_LIBRARIES(example_gl2 nanovg GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_gl2 PRIVATE NANOVG_GLEW)

ADD_EXECUTABLE(example_gl3 example/example_gl3.c example/demo.c example/perf.c)
TARGET_LINK_LIBRARIES(example_gl3 nanovg GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_gl3 PRIVATE NANOVG_GLEW)

ADD_EXECUTABLE(example_gles2 example/example_gles2.c example/demo.c example/perf.c)
TARGET_LINK_LIBRARIES(example_gles2 nanovg GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_gles2 PRIVATE NANOVG_GLEW)

ADD_EXECUTABLE(example_gles3 example/example_gles3.c example/demo.c example/perf.c)
TARGET_LINK_LIBRARIES(example_gles3 nanovg GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_gles3 PRIVATE NANOVG_GLEW)

ADD_EXECUTABLE(example_fbo example/example_fbo.c example/demo.c example/perf.c)
TARGET_LINK_LIBRARIES(example_fbo nanovg GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_fbo PRIVATE NANOVG_GLEW)

ADD_EXECUTABLE(example_svg1 example/example_svg1.c)
TARGET_LINK_LIBRARIES(example_svg1 nanovg GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_svg1 PRIVATE NANOVG_GLEW)

ADD_EXECUTABLE(example_svg2 example/example_svg2.c)
TARGET_LINK_LIBRARIES(example_svg2 nanovg GLEW EGL GL glfw m)
TARGET_COMPILE_DEFINITIONS(example_svg2 PRIVATE NANOVG_GLEW)
