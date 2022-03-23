NAME = fdf

C = gcc

C_FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS =	fdf.c arr_utils.c color.c hooks.c \
		map_info.c map_parse.c utils.c \
		move_map.c print_line.c print_map.c \
		print_utils.c gnl/get_next_line.c gnl/get_next_line_utils.c

OBJ = $(patsubst %.c,%.o,$(SRCS))

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C mlx
	@make -C libft
	$(CC) $(OBJ) mlx/libmlx.a libft/libft.a $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean :
	@rm -f $(OBJ)
	@make -C libft clean

fclean : clean
	@rm -f $(NAME)
	@make -C mlx clean
	@make -C libft fclean

re : fclean all

.PHONY : all clean fclean re
