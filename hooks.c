/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:02:47 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 22:14:05 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	choose_key_action2(int key, t_fdf *info)
{
	if (key == 13)
		info->rotate->x -= 6;
	else if (key == 1)
		info->rotate->x += 6;
	else if (key == 0)
		info->rotate->y -= 6;
	else if (key == 2)
		info->rotate->y += 6;
	else if (key == 12)
		info->rotate->z -= 6;
	else if (key == 14)
		info->rotate->z += 6;
	if (key == 49)
	{
		if (info->projection == 0)
			info->projection = 1;
		else
			info->projection = 0;
	}
}

void	choose_key_action(int key, t_fdf *info)
{
	if (key == 123)
		info->shift->x -= 6;
	else if (key == 124)
		info->shift->x += 6;
	else if (key == 125)
		info->shift->y += 6;
	else if (key == 126)
		info->shift->y -= 6;
	else
		choose_key_action2(key, info);
}

int	key_hook(int key, t_fdf *info)
{
	mlx_destroy_image(info->mlx_ptr, info->img->img);
	if (key == 53)
	{
		parsedmap_clear(info->map);
		free(info->img);
		free(info->rotate);
		free(info->shift);
		mlx_destroy_window(info->mlx_ptr, info->win_ptr);
		free(info);
		exit(0);
	}
	info->img->img = mlx_new_image(info->mlx_ptr, 1000, 1000);
	info->img->addr = mlx_get_data_addr(info->img->img,
			&info->img->bits_per_pixel,
			&info->img->line_length, &info->img->endian);
	choose_key_action(key, info);
	print_map(info);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img, 0, 0);
	return (0);
}

int	mouse_press(int key, int x, int y, t_fdf *info)
{
	(void)x;
	(void)y;
	mlx_destroy_image(info->mlx_ptr, info->img->img);
	info->img->img = mlx_new_image(info->mlx_ptr, 1000, 1000);
	info->img->addr = mlx_get_data_addr(info->img->img,
			&info->img->bits_per_pixel,
			&info->img->line_length, &info->img->endian);
	if (key == 4)
		info->scale *= 1.25;
	else if (key == 5)
		info->scale *= 0.8;
	print_map(info);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img, 0, 0);
	return (0);
}
