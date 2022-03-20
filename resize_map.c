#include "fdf.h"

angl	*ft_get_center(angl ***map)
{
	int 	i;
    int 	j;
	angl	*center;

    i = 0;
	j = 0;
	center = (angl *)malloc(sizeof(angl));
    while (map[i])
		i++;
	i--;
	while (map[i][j])
		j++;
	j--;
	center->x = map[i][j]->x / 2;
	center->y = map[i][j]->y / 2;
	return (center);
}

void    ft_set_size(angl ***map, double line_len)
{
    int i;
    int j;

    i = 0;
    while (map[i])
	{
		j = 0;
		while (map[i][j] != NULL)
		{
			map[i][j]->x *= line_len;
            map[i][j]->y *= line_len;
            map[i][j]->z *= line_len;
			j++;
		}
		i++;
	}
}

void    ft_set_to_center(angl ***map, float center)
{
    int i;
    int j;

    i = 0;
    while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->x -= center;
            map[i][j]->y -= center;
			j++;
		}
		i++;
	}
}

double	ft_set_normal_size(angl ***map, int x, int y, int z)
{
    int		i;
    int 	j;
    double	coefficient;

    i = 0;
    if (x > 500 && x >= y && x >= z)
        coefficient = x / 500;
    if (y > 500 && y >= x && y >= z)
        coefficient = y / 500;
    if (z > 500 && z >= x && z >= y)
        coefficient = z / 500;
    while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->x /= coefficient;
            map[i][j]->y /= coefficient;
            map[i][j]->z /= coefficient;
			j++;
		}
		i++;
	}
	return (coefficient);
}