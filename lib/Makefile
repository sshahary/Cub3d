
NAME		= full_libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

PRINT_SRC	= ft_printf/ft_printf.c ft_printf/ft_useful.c ft_printf/ft_useful_2.c
GNL_SRC		= gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c
SRC			= $(PRINT_SRC) $(GNL_SRC)
OBJ			= $(SRC:.c=.o)

LIBFT_PATH	= ./Libft
LIBFT		= $(LIBFT_PATH)/libft.a

all: $(NAME) clean

$(NAME): lib $(OBJ)
	cp $(LIBFT) $(NAME)
	ar -rcs $(NAME) $(OBJ)

lib :
	make -sC $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean:
	rm -f $(OBJ)
	make clean -C Libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C Libft/

re: fclean all

.PHONY: all lib clean fclean re