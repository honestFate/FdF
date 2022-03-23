/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:15:38 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 22:12:33 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_to_center(t_angl ***map, t_angl *center)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->x = map[i][j]->x - center->x;
			map[i][j]->y = map[i][j]->y - center->y;
			map[i][j]->z = map[i][j]->z - center->z;
			j++;
		}
		i++;
	}
}

void	set_size(t_angl *point, double line_len)
{
	point->x *= line_len;
	point->y *= line_len;
	point->z *= line_len;
}

void	rotate_point(t_angl *point, int angle, int ax)
{
	float	arg;
	int		p2;

	arg = (angle * M_PI) / 180;
	if (ax == 0)
	{
		p2 = -(point->y) * sin(arg) + point->z * cos(arg);
		point->y = point->y * cos(arg) + point->z * sin(arg);
		point->z = p2;
	}
	if (ax == 1)
	{
		p2 = -(point)->x * sin(arg) + point->z * cos(arg);
		point->x = point->x * cos(arg) + point->z * sin(arg);
		point->z = p2;
	}
	if (ax == 2)
	{
		p2 = point->x * sin(arg) + point->y * cos(arg);
		point->x = point->x * cos(arg) - point->y * sin(arg);
		point->y = p2;
	}
}
