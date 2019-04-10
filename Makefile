CC = gcc
FLAGS = -Wall -Wextra -Werror
GLFLAGS = -framework CoreVideo -framework OpenGL -framework IOKit -framework AppKit -L $(LIB_PATH)glfw/build/src -lglfw3

EXEC_NAME = scop
SRC_FILES = main.c \
			glad.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./lib/
INC_PATH = ./inc/

SRCS = $(addprefix $(SRC_PATH),$(SRC_FILES))
OBJS = $(addprefix $(OBJ_PATH),$(OBJ_FILES))
INCS = -I $(INC_PATH) -I $(LIB_PATH)glfw/include/ -I $(LIB_PATH)libft/

.PHONY : all clean fclean re

all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJS)
	make -C $(LIB_PATH)libft
	cmake -S $(LIB_PATH)glfw -B $(LIB_PATH)glfw/build
	make -C $(LIB_PATH)glfw/build
	@$(CC) $(FLAGS) $(GLFLAGS) -o $(EXEC_NAME) $(OBJS)
	@echo "$(EXEC_NAME) compiled ✓"

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) $(INCS) -o $@ -c $<
	@echo "$@ created ✓"

clean :
	@/bin/rm -rf $(OBJ_PATH)
	@echo "Objects cleaned ✓"

fclean : clean
	@/bin/rm -f $(EXEC_NAME)
	@/bin/rm -rf $(LIB_PATH)glfw/build
	@echo "$(EXEC_NAME) deleted ✓"
re : 
	$(MAKE) fclean
	$(MAKE) all
