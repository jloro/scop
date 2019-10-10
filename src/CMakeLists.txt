cmake_minimum_required(VERSION 3.0)

set(SRCS
	main.c
	xpm.c
	init.c
	callback.c
	callback_utils.c
	init_mat.c
	parsing.c
	parsing_utils.c
	shader.c)

include_directories(${scop_SOURCE_DIR}/inc)
include_directories(${scop_SOURCE_DIR}/lib/glfw/include)
include_directories(${scop_SOURCE_DIR}/lib/libft/inc)
include_directories(${scop_SOURCE_DIR}/lib/libmat/inc)
include_directories(${scop_SOURCE_DIR}/lib/glad)

link_directories(${scop_SOURCE_DIR}/lib/libft/src)
link_directories(${scop_SOURCE_DIR}/lib/libmat)
link_directories(${scop_SOURCE_DIR}/lib/glad)

add_executable(scop ${SRCS} ${INCS})

target_link_libraries(scop ft mat glfw glad)
