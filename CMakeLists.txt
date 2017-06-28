cmake_minimum_required(VERSION 3.0)

option(NA_BUILD_EXAMPLE "Build the Nimble App example" ON)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")

find_package(GLEW REQUIRED)

add_subdirectory(ext/glfw)

add_library(nimbleapp
	ext/nanovg/src/fontstash.h
	ext/nanovg/src/nanovg.c
	ext/nanovg/src/nanovg.h
	ext/nanovg/src/nanovg_gl.h
	ext/nanovg/src/nanovg_gl_utils.h
	ext/nanovg/src/stb_image.h
	ext/nanovg/src/stb_truetype.h

	src/scratch2.cpp
	src/layout.cpp
	src/nanovg.cpp

	src/nimble/app.cpp
	src/nimble/widget.cpp
	src/nimble/bounds.cpp
	src/nimble/widgets/rect.cpp
	src/nimble/widgets/button.cpp
)

include_directories(
	ext/nanovg/src/
	ext/scratch2/scratch2/
	ext/layout/
	ext/glm/glm/
	include/
	${GLEW_INCLUDE_DIRS}
)

target_link_libraries(nimbleapp
	glfw
	GL
	${GLEW_LIBRARIES}
)

if(NA_BUILD_EXAMPLE)
	add_subdirectory(example)
endif()
