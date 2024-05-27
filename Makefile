NAME		= cub3d

CFLAGS		= -Wall -Wextra -Werror
SRCS		= main.c src/raycasting.c src/raycastutilis.c src/rendering.c
OBJS		= ${SRCS:.c=.o}

MLX_URL		= https://github.com/codam-coding-college/MLX42.git
MLX_PATH	= ./MLX42/build
MLX			= $(MLX_PATH)/libmlx42.a
LIBMLX		= ./MLX42
MLX_FLAGS	= -L$(MLX_PATH) -lmlx42 -ldl -lglfw -framework Cocoa -framework OpenGL -framework IOKit -pthread -lm

LIB_PATH	= ./lib
LIB			= $(LIB_PATH)/full_libft.a
HEADERS		= -I ./include -I $(LIBMLX)/include

all: $(MLX) $(LIB) $(NAME) clean

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(LIB) $(MLX_FLAGS) -o $(NAME)
	@printf "Compiled successfully\nRun with:   ./cub3d \"map_file.cub\"\n"

$(MLX):
	@if [ ! -d "$(LIBMLX)" ]; then \
		git clone $(MLX_URL); \
	fi
	cd MLX42 && cmake -B build && cmake --build build

$(LIB):
	@make -sC $(LIB_PATH)

clean:
	@rm -rf $(OBJS)
	@make -sC $(LIB_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)
	@make -sC $(LIB_PATH) fclean

re: clean all

.PHONY: all, clean, fclean, re