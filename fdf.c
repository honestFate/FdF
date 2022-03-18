#include "fdf.h"
#include "mlx/mlx.h"

/*void ft_rotate_axis_x(angl point)
{

}*/

/*int ft_get_angle(int mod, int axis, int angle)
{
	static	i;
}*/

void ft_map_clear(void ***map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			free(map[i][j]);
			j++;
		}
		free(map[i][j]);
		free(map[i]);
		i++;
	}
	free(map[i]);
	free(map);
}

char ***ft_resize_arr(char ***map, int map_current_size)
{
	int		i;
	int		j;
	char	***new_map;

	i = 0;
	new_map = malloc((map_current_size + MAP_SIZE) * sizeof(char ***));
	while (i < map_current_size)
	{
		j = 0;
		while (map[i][j])
		{		
			new_map[i][j] = map[i][j];
			j++;
		}
		new_map[i][j] = map[i][j];
		free(map[i]);
		i++;
	}
	free(map);
	return (new_map);
}

void ft_putline_map(char ***map, char *line, int i)
{
	if (i % MAP_SIZE == 0 && i != 0)
		map = ft_resize_arr(map, i);
	if (!line)
	{
		map[i] = NULL;
		return ;
	}
	else
		map[i] = ft_split(line, ' ');
	free(line);
}

char ***ft_get_map(int fd)
{
	int		i;
	char	*line;
	char	***map;

	map = (char ***)malloc(MAP_SIZE * sizeof(char **));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		ft_putline_map(map, line, i);
		line = get_next_line(fd);
		i++;
	}
	ft_putline_map(map, line, i);
	return (map);
}

int	fill_angl_line(char ***map, angl ***map_parsed, int i, int line_len)
{
	int j;

	j = 0;
	while (map[i][j])
	{
		map_parsed[i][j] = (angl *)malloc(sizeof(angl));
		(map_parsed[i][j])->x = j;
		(map_parsed[i][j])->y = i;
		(map_parsed[i][j])->z = (double)ft_atoi(map[i][j]);
		j++; 
	}
	map_parsed[i][j] = NULL;
	if (j != line_len)
	{
		ft_map_clear((void ***)map_parsed);
		map_parsed = NULL;
		return (0);
	}
	return (1);
}

angl ***ft_map_parse(char ***map)
{
	int 	i;
	int		line_len;
	angl	***map_parsed;

	line_len = 0;
	i = 0;
	while (map[i])
		i++;
	while (map[0][line_len])
		line_len++;
	map_parsed = (angl ***)malloc((i + 1) * sizeof(angl **));
	ft_putnbr_fd(i, 1);
	i = 0;
	while (map[i])
	{
		map_parsed[i] = (angl **)malloc(line_len * sizeof(angl *));
		if (!fill_angl_line(map, map_parsed, i, line_len))
			break ;
		i++;
	}
	map_parsed[i] = malloc(sizeof(angl **));
	ft_putnbr_fd(i, 1);
	map_parsed[i] = NULL;
	ft_putnbr_fd((int)map_parsed[i], 1);
	ft_putendl_fd("", 1);
	ft_map_clear((void ***)map);
	return (map_parsed);
}

int main(int argc, char **argv)
{
    void    *mlx_ptr;
    void    *win_ptr;
	int 	fd;
	char	***map;
	angl	***map_parsed;
	t_data_img	img;

	if (argc != 2)
		return (0);
    fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	map = ft_get_map(fd);
	close(fd);
	if (map[0][0] == NULL)
	{
		ft_map_clear((void ***)map);
		return (0);
	}
	map_parsed = ft_map_parse(map);
	if (map_parsed == NULL)
		return (0);
	int i, j;
	i = 0;
	while (map_parsed[i])
	{
		j = 0;
		while (map_parsed[i][j])
		{
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(" ", 1);
			ft_putnbr_fd(j, 1);
			ft_putstr_fd("  ", 1);
			j++;
		}
		ft_putendl_fd("", 1);
		i++;
	}
	printf("%p\n", map_parsed[i]);
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 700, 700, "FdF");
	img.img = mlx_new_image(mlx_ptr, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	ft_set_size(map_parsed, 20);
	ft_putendl_fd("start", 1);
	ft_print_map(map_parsed, &img);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
    mlx_loop(mlx_ptr);
}