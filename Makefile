NAME = wodices
SRC = WoDlauncher.c utilities.c parser.c
SRC_PATH = src
OBJ_PATH = obj
OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)

CC = gcc
FLAGS = -Iincludes -O3 -lsodium

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@$(CC) $(FLAGS) -c $< -o $@

clean : 
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
