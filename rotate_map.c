#include "fdf.h"

void    ft_rotate_point(angl *point, int angle, int ax)
{
    if (ax == 0)
    {
        point->y = point->y * cos(angle) + point->z * sin(angle);
        point->z = -(point->y) * sin(angle) + point->z * cos(angle);
    }
    if (ax == 1)
    {
        point->x = point->x * cos(angle) + point->z * sin(angle);
        point->z = -(point)->x * sin(angle) + point->z * cos(angle);
    }
    if (ax == 2)
    {
        point->x = point->y * cos(angle) + point->z * sin(angle);
        point->y = -(point)->y * sin(angle) + point->z * cos(angle);
    }
}

void    ft_rotate_map(angl ***map, int angle, int ax)
{
    int i;
    int j;

    i = 0;
    while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ft_rotate_point(map[i][j], angle, ax);
			j++;
		}
		i++;
	}
}