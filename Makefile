CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = pipex.c cmd_ext.c proc_pipes.c
OBJ = $(SRC:.c=.o)
NAME = pipex


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

bonus : all

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
