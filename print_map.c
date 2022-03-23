/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:04:37 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 23:08:06 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_line_v(t_line *line)
{
	double	grad;
	double	temp;

	grad = (double)line->dx / (double)line->dy;
	if (line->end->y < line->start->y)
		swap(line->start, line->end);
	if (line->end->x < line->start->x)
		grad = -grad;
	temp = line->start->x + grad;
	put_pixel_img(line->img, line->start->x, line->start->y, line->color);
	line->start->y = line->start->y + 1;
	while (line->start->y < line->end->y)
	{
		put_pixel_img(line->img, i_part(temp), line->start->y,
			create_trgb((int)(f_part(temp) * 255), get_r(line->color),
				get_g(line->color), get_b(line->color)));
		put_pixel_img(line->img, i_part(temp) + 1, line->start->y,
			create_trgb(255 - (int)(f_part(temp) * 255), get_r(line->color),
				get_g(line->color), get_b(line->color)));
		temp += grad;
		(line->start->y)++;
	}
	put_pixel_img(line->img, line->end->x, line->end->y, line->color);
}

void	print_line_h(t_line *line)
{
	double	grad;
	double	temp;

	grad = (double)line->dy / (double)line->dx;
	if (line->end->x < line->start->x)
		swap(line->start, line->end);
	if (line->end->y < line->start->y)
		grad = -grad;
	temp = line->start->y + grad;
	put_pixel_img(line->img, line->start->x, line->start->y, line->color);
	line->start->x = line->start->x + 1;
	while (line->start->x < line->end->x)
	{
		put_pixel_img(line->img, line->start->x, i_part(temp),
			create_trgb((int)(f_part(temp) * 255), get_r(line->color),
				get_g(line->color), get_b(line->color)));
		put_pixel_img(line->img, line->start->x, i_part(temp) + 1,
			create_trgb(255 - (int)(f_part(temp) * 255), get_r(line->color),
				get_g(line->color), get_b(line->color)));
		temp += grad;
		(line->start->x)++;
	}
	put_pixel_img(line->img, line->end->x, line->end->y, line->color);
}

void	print_line(t_line *line)
{
	if (line->end->x > line->start->x)
		line->dx = line->end->x - line->start->x;
	else
		line->dx = line->start->x - line->end->x;
	if (line->end->y > line->start->y)
		line->dy = line->end->y - line->start->y;
	else
		line->dy = line->start->y - line->end->y;
	if (line->dx == 0)
		print_simple_linex(line->start, line->end, line->img, line->color);
	else if (line->dy == 0)
		print_simple_liney(line->start, line->end, line->img, line->color);
	else if (line->dy < line->dx)
		print_line_h(line);
	else
		print_line_v(line);
}

void	print_two_line(t_fdf *fdf, t_line *line, int i, int j)
{
	line->color = choose_color(fdf->map[i][j]->z);
	if (fdf->map[i][j + 1])
	{
		line->start = point_move(fdf->map[i][j], fdf);
		line->end = point_move(fdf->map[i][j + 1], fdf);
		print_line(line);
		free(line->start);
		free(line->end);
	}
	if (fdf->map[i + 1] != NULL)
	{
		line->start = point_move(fdf->map[i][j], fdf);
		line->end = point_move(fdf->map[i + 1][j], fdf);
		print_line(line);
		free(line->start);
		free(line->end);
	}
}

void	print_map(t_fdf *fdf)
{
	int		i;
	int		j;
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->img = fdf->img;
	i = 0;
	while (fdf->map[i] != NULL)
	{
		j = 0;
		while (fdf->map[i][j])
		{
			print_two_line(fdf, line, i, j);
			j++;
		}
		i++;
	}
	free(line);
}
