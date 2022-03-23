/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:00:47 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 23:02:20 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_angl	*get_center(t_angl ***map)
{
	int		i;
	int		j;
	int		lowest;
	t_angl	*center;

	i = 0;
	j = 0;
	center = (t_angl *)malloc(sizeof(t_angl));
	while (map[i])
		i++;
	i--;
	while (map[i][j])
		j++;
	j--;
	center->x = map[0][j]->x / 2;
	center->y = map[i][0]->y / 2;
	lowest = get_lowest(map);
	center->z = ((get_peak(map) - lowest) / 2) + lowest;
	return (center);
}

double	get_map_scale(t_angl *center)
{
	double	scale;

	if (center->x >= center->y && center->x >= center->z)
		scale = 250 / center->x;
	else if (center->y >= center->x && center->y >= center->z)
		scale = 250 / center->y;
	else
		scale = 250 / center->z;
	return (scale);
}

float	get_lowest(t_angl ***map)
{
	int		i;
	int		j;
	float	lowest;

	lowest = map[0][0]->z;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j]->z < lowest)
				lowest = map[i][j]->z;
			j++;
		}
		i++;
	}
	return (lowest);
}

float	get_peak(t_angl ***map)
{
	int		i;
	int		j;
	float	peak;

	peak = map[0][0]->z;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j]->z > peak)
				peak = map[i][j]->z;
			j++;
		}
		i++;
	}
	return (peak);
}
