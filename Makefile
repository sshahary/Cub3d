NAME		= cub3d

CFLAGS		= -Wall -Wextra -Werror
SRCS		= main.c
# BONUS =
OBJS		= ${SRCS:.c=.o}
MLX_URL		= https://github.com/codam-coding-college/MLX42.git
MLX_PATH	= ./MLX42/build
MLX			= $(MLX_PATH)/libmlx42.a
LIBMLX		= ./MLX42
MLX_FLAGS	= -ldl -lglfw -pthread -lm
# GNL_PATH	= ./gnl
# GNL			= $(GNL_PATH)/get_next_line.a
LIB_PATH	= ./lib/ft_print
LIB			= $(LIB_PATH)/libftprintf.a
HEADERS		= -I ./include -I $(LIBMLX)/include $(MLX_FLAGS)

all: $(MLX) $(LIB) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(MLX):
	git clone $(MLX_URL)
	cd MLX42 && cmake -B build && cmake --build build

$(LIB):
	@make -sC $(LIB_PATH)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LIB) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)
	@make -C $(LIB_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB_PATH) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx