/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 13:33:44 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/06/07 15:56:31 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_width(char *map, int *pointer)
{
	int	i;
	int	width;
	int	max_width;
	int	height;

	max_width = 0;
	height = 0;
	i = 0;
	width = 0;
	while (map[i])
	{
		if (map[i] == '\n')
		{
			if (max_width < width)
				max_width = width;
			++height;
			width = 0;
		}
		width++;
		i++;
	}
	*pointer = height + 1;
	return (max_width);
}

void	get_map_size(t_parsing *data)
{
	data->map_width = get_width(data->map, &data->map_height);
}

int	**set_two(t_parsing *data)
{
	int	**map_flood;
	int	i;
	int	j;

	i = 0;
	j = 0;
	map_flood = (int **)malloc(sizeof(int *) * data->map_height);
	while (j < data->map_height)
	{
		i = 0;
		map_flood[j] = (int *)malloc(sizeof(int) * data->map_width);
		while (i < data->map_width)
		{
			map_flood[j][i] = 2;
			i++;
		}
		j++;
	}
	return (map_flood);
}

int	init_piece(t_parsing *data, int j, int i, int index)
{
	if (j == data->map_height - 1)
	{
		i = -1;
		while (++i < data->map_width)
		{
			data->map_flood[j][i] = 2;
		}
		return (1);
	}
	data->map_flood[j][i] = set_value(data->map[index], data, j, i);
	if (data->map[index] == '\n' && i < data->map_width - 1)
	{
		while (i < data->map_width - 1)
		{
			data->map_flood[j][i] = 2;
			i++;
		}
	}
	return (1);
}

int	init_map(t_parsing *data)
{
	int	i;
	int	j;
	int	index;

	j = 0;
	index = 0;
	get_map_size(data);
	data->map_flood = set_two(data);
	while (j < data->map_height)
	{
		i = 0;
		while (i < data->map_width)
		{
			if (!add_last_line_2(data, &j))
				break ;
			data->map_flood[j][i] = set_value(data->map[index], data, j, i);
			if (data->map[index] == '\n' && i < data->map_width - 1)
				while (i < data->map_width - 1)
					data->map_flood[j][i++] = 2;
			index++;
			i++;
		}
		j++;
	}
	return (1);
}
