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
	include/nimble/widgetselector.h
	include/nimble/widgetevent.h
	include/nimble/content.h
	include/nimble/contentnode.h
	include/nimble/layoutloader.h

	src/nimble/app.cpp
	src/nimble/contentmanager.cpp
	src/nimble/widget.cpp
	src/nimble/widgetselector.cpp
	src/nimble/widgetevent.cpp
	src/nimble/content.cpp
	src/nimble/contentnode.cpp
	src/nimble/layoutloader.cpp
)

set(SRC_NIMBLE_WIDGETS
	include/nimble/widgets/page.h
	include/nimble/widgets/rect.h
	include/nimble/widgets/button.h
	include/nimble/widgets/label.h
	include/nimble/widgets/text.h

	src/nimble/widgets/page.cpp
	src/nimble/widgets/rect.cpp
	src/nimble/widgets/button.cpp
	src/nimble/widgets/label.cpp
	src/nimble/widgets/text.cpp
)

set(SRC_NIMBLE_UTILS
	include/nimble/utils/utils.h
	include/nimble/utils/bounds.h
	include/nimble/utils/ini.h
	include/nimble/utils/localization.h

	src/nimble/utils/utils.cpp
	src/nimble/utils/bounds.cpp
	src/nimble/utils/ini.cpp
	src/nimble/utils/localization.cpp
)

set(SRC_NIMBLE_CONTENT
	include/nimble/content/font.h

	src/nimble/content/font.cpp
)

set(SRC_NIMBLE_CONTENT_NODES
	include/nimble/content/nodes/layoutnode.h

	src/nimble/content/nodes/layoutnode.cpp
)

add_library(nimbleapp
	${SRC_EXT}
	${SRC}
	${SRC_NIMBLE}
	${SRC_NIMBLE_WIDGETS}
	${SRC_NIMBLE_UTILS}
	${SRC_NIMBLE_CONTENT}
	${SRC_NIMBLE_CONTENT_NODES}
)

source_group("ext" FILES ${SRC_EXT})
source_group("src" FILES ${SRC})
source_group("src\\nimble" FILES ${SRC_NIMBLE})
source_group("src\\nimble\\utils" FILES ${SRC_NIMBLE_UTILS})
source_group("src\\nimble\\widgets" FILES ${SRC_NIMBLE_WIDGETS})
source_group("src\\nimble\\content" FILES ${SRC_NIMBLE_CONTENT})
source_group("src\\nimble\\content\\nodes" FILES ${SRC_NIMBLE_CONTENT_NODES})

set(INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	${CMAKE_CURRENT_SOURCE_DIR}/ext/scratch2/scratch2/
	${CMAKE_CURRENT_SOURCE_DIR}/ext/glm/glm/
)

set(NIMBLE_APP_INCLUDE_DIRS ${INCLUDES} PARENT_SCOPE)

include_directories(
	${INCLUDES}
	ext/stb/
	ext/nanovg/src/
	ext/layout/
	ext/irrxml/
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
