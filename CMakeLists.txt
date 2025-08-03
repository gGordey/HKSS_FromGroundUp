cmake_minimum_required(VERSION 3.6...4.0)

project(HKSS_FromGroundUp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
include_directories(lib/glfw/include)
include_directories(lib/glad/include)

add_subdirectory(lib/glfw) # glfw
add_subdirectory(lib) # libgraphics (open gl + glfw + glad) 
add_subdirectory(src) # executable (shaw)

add_custom_target(res-folder ALL
	COMMAND rm -r "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res" || (exit 0)
	COMMAND cp -r 
       	"${CMAKE_SOURCE_DIR}/res/"
		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
