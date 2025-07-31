cmake_minimum_required(VERSION 3.8)

project(HKSS_FromGroundUp)

add_executable(shaw 
	main.c
)
target_link_libraries(shaw 
	glfw
	OpenGL::GL
)
