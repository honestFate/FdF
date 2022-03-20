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

void	ft_swap(double *x, double *y)
{
	double	temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void	put_pixel_img(t_data_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_print_simple_line(angl *start_point, angl *end_point, t_data_img *img, int color)
{
	if ((int)start_point->x == (int)end_point->x)
	{
		if (end_point->y < start_point->y)
			ft_swap(&(start_point->y), &(end_point->y));
		while (start_point->y <= end_point->y)
		{
			put_pixel_img(img, (int)roundl(start_point->x), (int)roundl(start_point->y), color);
			start_point->y++;
		}
	}
	else
	{
		if (end_point->x < start_point->x)
			ft_swap(&(start_point->x), &(end_point->x));
		while (start_point->x <= end_point->x)
		{
			put_pixel_img(img, (int)roundl(start_point->x), (int)roundl(start_point->y), color);
			start_point->x++;
		}
	}
}

angl *angl_copy(angl *p)
{
	angl	*copy;

	copy = (angl *)malloc(sizeof(angl));
	copy->x = p->x;
	copy->y = p->y;
	copy->z = p->z;
	return (copy);
}

void	ft_print_line(angl *start, angl *end, t_data_img *img, int color)
{
	//int		p;
	int		dx;
	int		dy;
	double	grad;
	double	temp;
	angl *start_point;
	angl *end_point;

	start_point = angl_copy(start);
	end_point = angl_copy(end);
	if (end_point->x > start_point->x)
		dx = end_point->x - start_point->x;
	else
		dx = start_point->x - end_point->x;
	if (end_point->y > start_point->y)
		dy = end_point->y - start_point->y;
	else
		dy = start_point->y - end_point->y;
	if (dx == 0 || dy == 0)
		ft_print_simple_line(start_point, end_point, img, color);
	else if (dy < dx)
	{
		grad = (double)dy / (double)dx;
		if (end_point->x < start_point->x)
		{
			ft_swap(&(start_point->x), &(end_point->x));
			ft_swap(&(start_point->y), &(end_point->y));
		}
		if(end_point->y < start_point->y)
			grad = -grad;
		temp = start_point->y + grad;
		put_pixel_img(img, start_point->x, start_point->y, color);
        start_point->x = start_point->x + 1;
		while (start_point->x < end_point->x)
		{
			put_pixel_img(img, start_point->x, i_part(temp), create_trgb((int)(f_part(temp) * 255), get_r(color), get_g(color), get_b(color)));
			put_pixel_img(img, start_point->x, i_part(temp) + 1, create_trgb(255 - (int)(f_part(temp) * 255), get_r(color), get_g(color), get_b(color)));
			temp += grad;
            (start_point->x)++;
		}
		put_pixel_img(img, end_point->x, end_point->y, color);
	}
	else
	{
		grad = (double)dx / (double)dy;
		if (end_point->y < start_point->y)
		{
			ft_swap(&(start_point->x), &(end_point->x));
			ft_swap(&(start_point->y), &(end_point->y));
		}
		if(end_point->x < start_point->x)
			grad = -grad;
		temp = start_point->x + grad;
		put_pixel_img(img, start_point->x, start_point->y, color);
        start_point->y = start_point->y + 1;
		while (start_point->y < end_point->y)
		{
			put_pixel_img(img, i_part(temp), start_point->y, create_trgb((int)(f_part(temp) * 255), get_r(color), get_g(color), get_b(color)));
			put_pixel_img(img, i_part(temp) + 1, start_point->y, create_trgb(255 - (int)(f_part(temp) * 255), get_r(color), get_g(color), get_b(color)));
			temp += grad;
            (start_point->y)++;
		}
		put_pixel_img(img, end_point->x, end_point->y, color);
	}
	free(start_point);
	free(end_point);
}

void    ft_print_map(angl ***map, t_data_img *img)
{
    int i;
    int j;
	int	color;

	color = create_trgb(0, 255, 255, 255);
    i = 0;
    while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j + 1])
				ft_print_line(map[i][j], map[i][j + 1], img, color);
			if (map[i + 1] != NULL)
				ft_print_line(map[i][j], map[i + 1][j], img, color);
			j++;
		}
		i++;
	}
}