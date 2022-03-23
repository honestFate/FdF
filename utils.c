/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:59:24 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 23:06:18 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	i_part(double x)
{
	return ((int)x);
}

double	f_part(double x)
{
	while (x >= 0)
		x--;
	x++;
	return (x);
}

void	swap(t_angl *s, t_angl *e)
{
	double	temp;

	temp = s->x;
	s->x = e->x;
	e->x = temp;
	temp = s->y;
	s->y = e->y;
	e->y = temp;
}

t_angl	*point_move(t_angl *point, t_fdf *fdf)
{
	t_angl	*new_point;

	new_point = angl_copy(point);
	set_size(new_point, fdf->scale);
	add_rotate(new_point, fdf->rotate);
	if (fdf->projection)
		to_iso(new_point);
	add_shift(new_point, fdf->shift);
	return (new_point);
}

int	choose_color(float z)
{
	if (z < 1)
		return (create_trgb(0, 255, 0, 0));
	else if (z > 1)
		return (create_trgb(0, 0, 0, 255));
	else
		return (create_trgb(0, 255, 255, 255));
}
