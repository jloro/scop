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

#symlink to access ressources
set (source "${CMAKE_SOURCE_DIR}/ressource")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/ressource")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
    DEPENDS ${destination}
    COMMENT "symbolic link ressource folder from ${source} => ${destination}"
)

#symlink to access shaders
set (source "${CMAKE_SOURCE_DIR}/shaders")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/shaders")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
    DEPENDS ${destination}
    COMMENT "symbolic link shaders folder from ${source} => ${destination}"
)
