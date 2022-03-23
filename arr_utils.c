/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:26:29 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 20:27:27 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_any_digit(char **s)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	while (s[i])
	{
		flag = 0;
		j = 0;
		while (s[i][j])
		{
			if (ft_isdigit(s[i][j]))
				flag = 1;
			j++;
		}
		if (!flag)
			return (0);
		i++;
	}
	return (1);
}

void	map_clear(char ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			free(map[i][j]);
			j++;
		}
		free(map[i][j]);
		free(map[i]);
		i++;
	}
	free(map[i]);
	while (i % (MAP_SIZE - 1) != 0)
		free(map[i++]);
	free(map);
}

void	parsedmap_clear(t_angl ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			free(map[i][j]);
			j++;
		}
		free(map[i][j]);
		free(map[i]);
		i++;
	}
	free(map[i]);
	free(map);
}

int	get_line_len(char **map)
{
	int		i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	***ft_resize_arr(char ***map, int map_current_size)
{
	int		i;
	int		j;
	int		line_len;
	char	***new_map;

	i = 0;
	line_len = get_line_len(map[i]);
	new_map = (char ***)malloc((map_current_size + 1 + MAP_SIZE)
			* sizeof(char **));
	while (i < map_current_size)
	{
		j = 0;
		new_map[i] = (char **)malloc((line_len + 1) * sizeof(char *));
		while (map[i][j])
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		new_map[i][j] = map[i][j];
		free(map[i]);
		i++;
	}
	free(map);
	return (new_map);
}
