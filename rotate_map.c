#include "fdf.h"

void    ft_rotate_point(angl *point, int angle, int ax)
{
    float   arg;
    int     p1;
    int     p2;

    arg = (angle * M_PI) / 180;
    if (ax == 0)
    {
        p1 = point->y * cos(arg) - point->z * sin(arg);
        p2 = -(point->y) * sin(arg) + point->z * cos(arg);
        point->y = p1;
        point->z = p2;
    }
    if (ax == 1)
    {
        p1 = point->x * cos(arg) + point->z * sin(arg);
        p2 = -(point)->x * sin(arg) + point->z * cos(arg);
        point->x = p1;
        point->z = p2;
    }
    if (ax == 2)
    {
        p1 = point->x * cos(arg) - point->y * sin(arg);
        p2 = point->x * sin(arg) + point->y * cos(arg);
        point->x = p1;
        point->y = p2;
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

void    to_isometric(angl ***map)
{
    int i;
    int j;
    int iso_x;
    int iso_y;

    i = 0;
    while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
            iso_x = map[i][j]->x - map[i][j]->y;
            iso_y = (map[i][j]->x + map[i][j]->y) / 2;
			map[i][j]->x = iso_x;
            map[i][j]->y = iso_y;
            printf("map[i][j]->y = %f\n", map[i][j]->y);
			j++;
		}
		i++;
	}
}