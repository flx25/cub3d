NAME = libft.a

SRC = $(shell find . -name "ft_*.c" ! -name "ft_lst*.c")
OBJ = $(SRC:.c=.o)

BONUS_SRC = $(shell find . -name "ft_lst*.c")
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.c.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

bonus:	$(OBJ) $(BONUS_OBJ)
	ar -rcs $(NAME) $(OBJ) $(BONUS_OBJ)

.PHONY: all clean fclean re bonus