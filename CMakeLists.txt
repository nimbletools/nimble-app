cmake_minimum_required(VERSION 3.0)

option(NA_BUILD_EXAMPLE "Build the Nimble App example" ON)

project(NimbleApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if(WIN32)
	set(MONO_LIBRARIES "" CACHE STRING "")
	set(MONO_INCLUDE_DIRS "" CACHE STRING "")

	if(NOT MONO_LIBRARIES OR NOT MONO_INCLUDE_DIRS)
		message(FATAL_ERROR "Mono is not defined, please set MONO_LIBRARIES and MONO_INCLUDE_DIRS!")
	endif()
else()
	find_package(PkgConfig REQUIRED)
	pkg_search_module(MONO REQUIRED mono-2)
endif()

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

set(SRC_NIMBLE_MANAGED
	include/nimble/managed/managedcode.h
	include/nimble/managed/managedclass.h

	src/nimble/managed/managedcode.cpp
	src/nimble/managed/managedclass.cpp
)

set(SRC_NIMBLE_MANAGED_INTERNAL
	include/nimble/managed/internal/widget.h
	include/nimble/managed/internal/contentnode.h

	src/nimble/managed/internal/widget.cpp
	src/nimble/managed/internal/contentnode.cpp
)

set(SRC_NIMBLE_WIDGETS
	include/nimble/widgets/managed.h
	include/nimble/widgets/rect.h
	include/nimble/widgets/button.h
	include/nimble/widgets/label.h

	src/nimble/widgets/managed.cpp
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
	${SRC_NIMBLE_MANAGED}
	${SRC_NIMBLE_MANAGED_INTERNAL}
	${SRC_NIMBLE_WIDGETS}
	${SRC_NIMBLE_CONTENT}
	${SRC_NIMBLE_CONTENT_NODES}
)

source_group("ext" FILES ${SRC_EXT})
source_group("src" FILES ${SRC})
source_group("src\\nimble" FILES ${SRC_NIMBLE})
source_group("src\\nimble\\managed" FILES ${SRC_NIMBLE_MANAGED})
source_group("src\\nimble\\managed\\internal" FILES ${SRC_NIMBLE_MANAGED_INTERNAL})
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
	${MONO_INCLUDE_DIRS}
)

target_link_libraries(nimbleapp
	glfw
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${MONO_LIBRARIES}
)

include_external_msproject(Nimble.App
	${CMAKE_SOURCE_DIR}/Nimble.App/Nimble.App.csproj
	TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
)

set_target_properties(Nimble.App PROPERTIES FOLDER Managed)

add_dependencies(nimbleapp Nimble.App)

if(WIN32)
	set(CMAKE_SUPPRESS_REGENERATION true)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if(NA_BUILD_EXAMPLE)
	add_subdirectory(example)

	include_external_msproject(Nimble.App.Example
		${CMAKE_SOURCE_DIR}/Nimble.App.Example/Nimble.App.Example.csproj
		TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
	)

	set_target_properties(Nimble.App.Example PROPERTIES FOLDER Managed)

	add_dependencies(example Nimble.App Nimble.App.Example)
endif()
