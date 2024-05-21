NAME = cub3d

CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -ldl -lglfw -pthread -lm

SRCS = main.c
# BONUS =

MLX_URL = https://github.com/codam-coding-college/MLX42.git
MLX_PATH = ./MLX42/build
MLX = $(MLX_PATH)/libmlx42.a

GNL_PATH = ./gnl
GNL = $(GNL_PATH)/get_next_line.a
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): lib $(SRCS)
	cc $(CFLAGS) $(SRCS) $(MAIN) $(GNL) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

lib: $(MLX)
	make -sC $(GNL_PATH)
	make -sC $(LIBFT_PATH)

$(MLX):
	git clone $(MLX_URL)
	cd MLX42 && cmake -B build && cmake --build build

bonus: lib $(BONUS) $(SRCS)
	cc $(CFLAGS) $(BONUS) $(SRCS) $(GNL) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

clean:
	make clean -sC $(GNL_PATH)
	make clean -sC $(LIBFT_PATH)
	

fclean: clean
	rm -f $(NAME)
	rm -rf MLX42
	make fclean -sC $(GNL_PATH)
	make fclean -sC $(LIBFT_PATH)

re: fclean all

.PHONY: all lib bonus clean fclean re