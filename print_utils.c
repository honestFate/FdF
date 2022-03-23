/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:20:43 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 22:00:16 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x > 999 || y > 999 || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_angl	*angl_copy(t_angl *p)
{
	t_angl	*copy;

	copy = (t_angl *)malloc(sizeof(t_angl));
	copy->x = p->x;
	copy->y = p->y;
	copy->z = p->z;
	return (copy);
}

void	add_shift(t_angl *p, t_angl *shift)
{
	p->x += shift->x;
	p->y += shift->y;
	p->z += shift->z;
}

void	add_rotate(t_angl *p, t_angl *rotate)
{
	rotate_point(p, rotate->x, 0);
	rotate_point(p, rotate->y, 1);
	rotate_point(p, rotate->z, 2);
}

void	to_iso(t_angl *p)
{
	int	temp_x;
	int	temp_y;

	temp_x = p->x;
	temp_y = p->y;
	p->x = (temp_x - temp_y) * cos(0.523599);
	p->y = -p->z + (temp_x + temp_y) * sin(0.523599);
}
