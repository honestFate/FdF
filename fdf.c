#include "fdf.h"
#include "mlx/mlx.h"

void map_clear(char ***map)
{
	int i;
	int j;

	i = 0;
	ft_putendl_fd("START MAP FREE", 1);
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
	while (i % (MAP_SIZE - 1) != 0)
		free(map[i++]);
	ft_putendl_fd("END MAP FREE", 1);
	free(map);
}

void parsedmap_clear(angl ***map)
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

int	get_line_len(char **map)
{
	int		i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char ***ft_resize_arr(char ***map, int map_current_size)
{
	int		i;
	int		j;
	int		line_len;
	char	***new_map;

	i = 0;
	line_len = get_line_len(map[i]);
	new_map = (char ***)malloc((map_current_size + 1 + MAP_SIZE) * sizeof(char **));
	while (i < map_current_size)
	{
		j = 0;
		new_map[i] = (char **)malloc((line_len + 1) * sizeof(char *));
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

char*** ft_putline_map(char ***map, char *line, int i)
{
	if (i % (MAP_SIZE - 1) == 0 && i != 0 && line != NULL)
		map = ft_resize_arr(map, i);
	if (line == NULL)
	{
		map[i] = NULL;
		return (map);
	}
	else
		map[i] = ft_split(line, ' ');
	return (map);
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
		map = ft_putline_map(map, line, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map = ft_putline_map(map, line, i);
	return (map);
}

void	fill_angl_line(char ***map, angl ***map_parsed, int i)
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
	line_len = get_line_len(map[0]);
	map_parsed = (angl ***)malloc((i + 1) * sizeof(angl **));
	i = 0;
	while (map[i])
	{
		map_parsed[i] = (angl **)malloc((line_len + 1) * sizeof(angl *));
		fill_angl_line(map, map_parsed, i);
		i++;
	}
	map_parsed[i] = NULL;
	map_clear(map);
	return (map_parsed);
}

int	key_hook(int key, t_img *info)
{
	mlx_destroy_image(info->mlx_ptr, info->img->img);
	if (key == 53)
	{
		parsedmap_clear(info->map);
		free(info);
		exit(0);
	}
	info->img->img = mlx_new_image(info->mlx_ptr, 700, 700);
	info->img->addr = mlx_get_data_addr(info->img->img, &info->img->bits_per_pixel, &info->img->line_length,
								&info->img->endian);
	if (key == 123)
		ft_set_to_point(info->map, 5, 0, -1);
	else if (key == 124)
		ft_set_to_point(info->map, 5, 0, 1);
	else if (key == 125)
		ft_set_to_point(info->map, 0, 5, 1);
	else if (key == 126)
		ft_set_to_point(info->map, 0, 5, -1);
	ft_print_map(info->map, info->img);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img, 0, 0);
	return (0);
}

int mouse_press(int key, int x, int y, t_img *info)
{
	(void)x;
	(void)y;
	mlx_destroy_image(info->mlx_ptr, info->img->img);
	info->img->img = mlx_new_image(info->mlx_ptr, 700, 700);
	info->img->addr = mlx_get_data_addr(info->img->img, &info->img->bits_per_pixel, &info->img->line_length,
								&info->img->endian);
	if (key == 4)
		ft_set_size(info->map, 1.25);
	else if (key == 5)
		ft_set_size(info->map, 0.8);
	ft_print_map(info->map, info->img);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img, 0, 0);
	return (0);
}

int	ft_any_digit(char **s)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	while (s[i])
	{
		flag = 0;
		j = 0;
		while (s[i][j])
		{
			if (ft_isdigit(s[i][j]))
				flag = 1;
			j++;
		}
		if (!flag)
			return (0);
		i++;
	}
	return (1);
}

void	map_chech(char ***map)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = get_line_len(map[i]);
	while (map[i])
	{
		if (line_len != get_line_len(map[i]) || !ft_any_digit(map[i]))
		{
			map_clear(map);
			exit(0);
		}
		i++;
	}
}

int main(int argc, char **argv)
{
    void    *mlx_ptr;
    void    *win_ptr;
	int 	fd;
	char	***map;
	angl	***map_parsed;
	t_data_img	*img;

	img = (t_data_img *)malloc(sizeof(t_data_img));
	if (argc != 2)
		return (0);
    fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	map = ft_get_map(fd);
	ft_putendl_fd("READED", 1);
	close(fd);
	if (map[0] == NULL || get_line_len(map[0]) < 2 || map[1] == NULL)
	{
		map_clear(map);
		return (0);
	}
	map_chech(map);
	ft_putendl_fd("CHEKED", 1);
	map_parsed = ft_map_parse(map);
	if (map_parsed == NULL)
		return (0);
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 700, 700, "FdF");
	img->img = mlx_new_image(mlx_ptr, 700, 700);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	ft_set_size(map_parsed, 20);
	ft_set_to_point(map_parsed, 250, 150, 1);
	to_isometric(map_parsed);
	ft_print_map(map_parsed, img);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img->img, 0, 0);
	t_img *hook_info;
	hook_info = (t_img *)malloc(sizeof(t_img));
	hook_info->map = map_parsed;
	hook_info->win_ptr = win_ptr;
	hook_info->mlx_ptr = mlx_ptr;
	hook_info->img = img;
	mlx_key_hook(win_ptr, key_hook, hook_info);
	mlx_mouse_hook(win_ptr, mouse_press, hook_info);
    mlx_loop(mlx_ptr);
}