cmake_minimum_required(VERSION 3.6...4.0)

project(HKSS_FromGroundUp)

add_executable(shaw 
	main.c
	shader.c
	object.c
	io.c
	gl_wrapper.c
	texture.c
	renderable.c
)

target_link_libraries(shaw 
	graphics
)
