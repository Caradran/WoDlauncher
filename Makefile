NAME = wodices
SRC = WoDlauncher.c utilities.c parser.c
SRC_PATH = src
OBJ_PATH = obj
OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)

CC = gcc
FLAGS = -Iincludes

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ)

$(OBJ_PATH)/%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean : 
	@rm -rf $(OBJ_PATH)/$(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
