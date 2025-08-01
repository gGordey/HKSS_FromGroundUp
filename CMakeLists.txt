cmake_minimum_required(VERSION 3.6...4.0)

project(HKSS_FromGroundUp)

include_directories(include)
include_directories(lib/glfw/include)
include_directories(lib/glad/include)

add_subdirectory(lib/glfw) # glfw
add_subdirectory(lib) # libgraphics (open gl + glfw + glad) 
add_subdirectory(src) # executable
