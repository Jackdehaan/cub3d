/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_helper_functions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 16:47:44 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/06/07 15:56:25 by rfinneru      ########   odam.nl         */
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
			i++;
		}
		j++;
	}
}

int	set_value(char value, t_parsing *data, int y, int x)
{
	if (value == '1')
		return (1);
	else if (value == '0')
		return (0);
	else if (value == '\n')
		return (2);
	else if ((value == 'N' || value == 'E' || value == 'S' || value == 'W'))
	{
		data->player_direction = value;
		data->player_pos[0] = y + 0.5;
		data->player_pos[1] = x + 0.5;
		return (0);
	}
	else
		return (2);
}

double	ft_abs_double(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	add_last_line_2(t_parsing *data, int *j)
{
	int	i;

	i = -1;
	if ((*j) == data->map_height - 1)
	{
		while (++i < data->map_width)
			data->map_flood[(*j)][i] = 2;
		return (0);
	}
	return (1);
}
