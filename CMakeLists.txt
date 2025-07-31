cmake_minimum_required(VERSION 3.8)

project(HKSS_FromGroundUp)

find_package(OpenGL REQUIRED)

include_directories(lib/glfw/include)
add_subdirectory(lib/glfw)

add_subdirectory(src)
