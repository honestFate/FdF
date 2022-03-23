/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:57:16 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 23:02:16 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*create_fdf(t_fdf *fdf, char **argv)
{
	int		fd;
	char	***map;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = ft_get_map(fd);
	close(fd);
	if (map[0] == NULL || get_line_len(map[0]) < 2 || map[1] == NULL)
	{
		map_clear(map);
		return (NULL);
	}
	map_chech(map);
	fdf->map = ft_map_parse(map);
	if (fdf->map == NULL)
		return (NULL);
	fdf->img = (t_img *)malloc(sizeof(t_img));
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1000, 1000, "FdF");
	fdf->img->img = mlx_new_image(fdf->mlx_ptr, 1000, 1000);
	fdf->img->addr = mlx_get_data_addr(fdf->img->img,
			&fdf->img->bits_per_pixel,
			&fdf->img->line_length, &fdf->img->endian);
	return (fdf);
}

void	print_base_map(t_fdf *fdf)
{
	fdf->shift = get_center(fdf->map);
	set_to_center(fdf->map, fdf->shift);
	fdf->scale = get_map_scale(fdf->shift);
	fdf->shift->x = 499;
	fdf->shift->y = 499;
	fdf->rotate = (t_angl *)malloc(sizeof(t_angl));
	fdf->rotate->x = 0;
	fdf->rotate->y = 0;
	fdf->rotate->z = 0;
	fdf->projection = 1;
	print_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		return (0);
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (create_fdf(fdf, argv) == NULL)
	{
		free(fdf);
		return (0);
	}
	print_base_map(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, key_hook, fdf);
	mlx_do_key_autorepeaton(fdf->mlx_ptr);
	mlx_mouse_hook(fdf->win_ptr, mouse_press, fdf);
	mlx_loop(fdf->mlx_ptr);
}
