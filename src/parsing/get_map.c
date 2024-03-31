/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:33:44 by jade-haa          #+#    #+#             */
/*   Updated: 2024/03/31 15:29:04 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print2d_array(t_parsing *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (data->map_flood[j])
	{
		i = 0;
		while (data->map_flood[j][i])
		{
			printf("%d ", data->map_flood[j][i]);
			i++;
		}
		j++;
		printf("\n");
	}
}

int	set_value(char value)
{
	if (value == '1')
		return (1);
	else if (value == '0')
		return (0);
	else if (value == '\n')
		return (2);
	else if (value > 'A' && value < 'Z')
		return(0);
	else
		return (2);
}

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
	printf("%d | %d\n", data->map_width, data->map_height);
	// data->map_height = get_height(data->map);
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
			// printf("%c ", data->map[index]);
			map_flood[j][i] = 2;
			printf("%d ", map_flood[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
	printf("\n\n\n");
	return (map_flood);
}

int	init_map(t_parsing *data)
{
	int i;
	int j;
	int index;

	j = 0;
	i = 0;
	index = 0;
	get_map_size(data);
	data->map_flood = set_two(data);
	while (j < data->map_height)
	{
		i = 0;
		while (i < data->map_width)
		{
			data->map_flood[j][i] = set_value(data->map[index]);
			if (data->map[index] == '\n' && i < data->map_width - 1)
			{
				while (i < data->map_width - 1)
				{
					data->map_flood[j][i] = 2;
					printf("%d ", data->map_flood[j][i]);
					i++;
				}
			}
			printf("%d ", data->map_flood[j][i]);
			index++;
			i++;
		}
		printf("\n");
		j++;
	}
	return (1);
}
