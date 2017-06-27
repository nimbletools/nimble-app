cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")

add_subdirectory(ext/glfw)

add_executable(NimbleApp
	ext/nanovg/src/fontstash.h
	ext/nanovg/src/nanovg.c
	ext/nanovg/src/nanovg.h
	ext/nanovg/src/nanovg_gl.h
	ext/nanovg/src/nanovg_gl_utils.h
	ext/nanovg/src/stb_image.h
	ext/nanovg/src/stb_truetype.h

	src/scratch2.cpp
	src/layout.cpp

	src/main.cpp
)

include_directories(
	ext/nanovg/src/
	ext/scratch2/scratch2/
	ext/layout/
)

target_link_libraries(NimbleApp
	glfw
	GL
	GLEW
)
