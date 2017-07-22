cmake_minimum_required(VERSION 3.0)

option(NA_BUILD_EXAMPLE "Build the Nimble App example" ON)

project(NimbleApp)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(ext/glfw)

set(SRC_EXT
	ext/nanovg/src/fontstash.h
	ext/nanovg/src/nanovg.c
	ext/nanovg/src/nanovg.h
	ext/nanovg/src/nanovg_gl.h
	ext/nanovg/src/nanovg_gl_utils.h
	ext/nanovg/src/stb_image.h
	ext/nanovg/src/stb_truetype.h

	ext/irrxml/CXMLReaderImpl.h
	ext/irrxml/fast_atof.h
	ext/irrxml/heapsort.h
	ext/irrxml/irrArray.h
	ext/irrxml/irrString.h
	ext/irrxml/irrTypes.h
	ext/irrxml/irrXML.cpp
	ext/irrxml/irrXML.h
)

set(SRC
	src/scratch2.cpp
	src/layout.cpp
	src/nanovg.cpp
)

set(SRC_NIMBLE
	include/nimble/common.h

	include/nimble/app.h
	include/nimble/contentmanager.h
	include/nimble/widget.h
	include/nimble/bounds.h
	include/nimble/content.h
	include/nimble/contentnode.h
	include/nimble/layoutloader.h
	include/nimble/utils.h
	include/nimble/ini.h
	include/nimble/widgetselector.h

	src/nimble/app.cpp
	src/nimble/contentmanager.cpp
	src/nimble/widget.cpp
	src/nimble/bounds.cpp
	src/nimble/content.cpp
	src/nimble/contentnode.cpp
	src/nimble/layoutloader.cpp
	src/nimble/utils.cpp
	src/nimble/ini.cpp
	src/nimble/widgetselector.cpp
)

set(SRC_NIMBLE_WIDGETS
	include/nimble/widgets/rect.h
	include/nimble/widgets/button.h
	include/nimble/widgets/label.h

	src/nimble/widgets/rect.cpp
	src/nimble/widgets/button.cpp
	src/nimble/widgets/label.cpp
)

set(SRC_NIMBLE_CONTENT
	include/nimble/content/font.h

	src/nimble/content/font.cpp
)

set(SRC_NIMBLE_CONTENT_NODES
	include/nimble/content/nodes/layoutnode.h
	include/nimble/content/nodes/stylenode.h

	src/nimble/content/nodes/layoutnode.cpp
	src/nimble/content/nodes/stylenode.cpp
)

add_library(nimbleapp
	${SRC_EXT}
	${SRC}
	${SRC_NIMBLE}
	${SRC_NIMBLE_WIDGETS}
	${SRC_NIMBLE_CONTENT}
	${SRC_NIMBLE_CONTENT_NODES}
)

source_group("ext" FILES ${SRC_EXT})
source_group("src" FILES ${SRC})
source_group("src\\nimble" FILES ${SRC_NIMBLE})
source_group("src\\nimble\\widgets" FILES ${SRC_NIMBLE_WIDGETS})
source_group("src\\nimble\\content" FILES ${SRC_NIMBLE_CONTENT})
source_group("src\\nimble\\content\\nodes" FILES ${SRC_NIMBLE_CONTENT_NODES})

include_directories(
	ext/nanovg/src/
	ext/scratch2/scratch2/
	ext/layout/
	ext/glm/glm/
	ext/irrxml/
	include/
	${GLEW_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIR}
)

target_link_libraries(nimbleapp
	glfw
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
)

if(WIN32)
	set(CMAKE_SUPPRESS_REGENERATION true)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if(NA_BUILD_EXAMPLE)
	add_subdirectory(example)
endif()
