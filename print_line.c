/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:18:18 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 20:37:40 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_simple_linex(t_angl *start_point, t_angl *end_point,
		t_img *img, int color)
{
	if (end_point->y < start_point->y)
		swap(start_point, end_point);
	while (start_point->y <= end_point->y)
	{
		put_pixel_img(img, (int)roundl(start_point->x),
			(int)roundl(start_point->y), color);
		start_point->y++;
	}
}

void	print_simple_liney(t_angl *start_point, t_angl *end_point,
		t_img *img, int color)
{
	if (end_point->x < start_point->x)
		swap(start_point, end_point);
	while (start_point->x <= end_point->x)
	{
		put_pixel_img(img, (int)roundl(start_point->x),
			(int)roundl(start_point->y), color);
		start_point->x++;
	}
}
