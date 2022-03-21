#include "fdf.h"

void    ft_set_to_point(angl ***map, float x, float y, int sign)
{
    int i;
    int j;

    i = 0;
    while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->x = map[i][j]->x + x * sign;
            map[i][j]->y = map[i][j]->y + y * sign;
			j++;
		}
		i++;
	}
}