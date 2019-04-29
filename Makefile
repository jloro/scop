CC = gcc
FLAGS = -Wall -Wextra -Werror
GLFLAGS = -framework CoreVideo -framework OpenGL -framework IOKit -framework AppKit
LIBFLAGS = -lglfw3 -lft -lmat
LIB_GLAD = $(LIB_PATH)/glad/glad.c

EXEC_NAME = scop
SRC_FILES = main.c \
			xpm.c \
			init.c \
			callback.c \
			init_mat.c \
			parsing.c \
			parsing_utils.c \
			shader.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./lib/
INC_PATH = ./inc/ $(LIB_PATH)glfw/include/ $(LIB_PATH)libft/ $(LIB_PATH)libmat/inc $(LIB_PATH)/glad

LIBS = libmat libft glfw/build/src

SRCS = $(addprefix $(SRC_PATH),$(SRC_FILES))
OBJS = $(addprefix $(OBJ_PATH),$(OBJ_FILES))
INCS = $(addprefix -I, $(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIBS))

.PHONY : all clean fclean re

all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJS)
	@make -C $(LIB_PATH)libft
	@make -C $(LIB_PATH)libmat
	@$(CC) $(FLAGS) $(LIB) $(LIBFLAGS) $(GLFLAGS) $(LIB_GLAD) -o $(EXEC_NAME) $(OBJS)
	@echo "$(EXEC_NAME) compiled ✓"

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) $(INCS) -o $@ -c $<
	@echo "$@ created ✓"

clean :
	@make -C $(LIB_PATH)libmat clean
	@make -C $(LIB_PATH)libft clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "Objects cleaned ✓"

fclean : clean
	@make -C $(LIB_PATH)libmat fclean
	@make -C $(LIB_PATH)libft fclean
	@/bin/rm -f $(EXEC_NAME)
	@echo "$(EXEC_NAME) deleted ✓"
re :
	$(MAKE) fclean
	$(MAKE) all
