NAME = fdf

C = gcc

C_FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS =	fdf.c gnl/get_next_line.c gnl/get_next_line_utils.c

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

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
