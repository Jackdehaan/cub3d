/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/08 15:28:43 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/15 13:57:32 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	check_if_start_pos(t_parsing *data)
{
	int		i;
	bool	found_starting_pos;

	i = 0;
	found_starting_pos = false;
	while (data->map[i])
	{
		if (data->map[i] == 'S' || data->map[i] == 'N' || data->map[i] == 'W'
			|| data->map[i] == 'E')
		{
			if (found_starting_pos)
				return (write(STDOUT_FILENO,
						"Found multiple starting positions\n", 34), false);
			found_starting_pos = true;
		}
		i++;
	}
	if (!found_starting_pos)
		write(STDOUT_FILENO, "Didn't find starting position\n", 30);
	return (found_starting_pos);
}


int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == '\n');
}

int	invalid_char(t_parsing *data)
{
	int		i;
	bool	found_zero;

	found_zero = false;
	i = 0;
	while (data->map[i])
	{
		if (!valid_char(data->map[i]))
			return (free_data(data), write(STDERR_FILENO, "Invalid input inside map\n", 25), 0);
		if (data->map[i] == '0')
			found_zero = true;
		i++;
	}
	if (!found_zero)
		return (free_data(data), write(STDERR_FILENO, "Map is too small\n", 17), 0);
	return (1);
}

int	valid_map(t_parsing *data)
{
	if (!invalid_char(data))
		return (0);
	if (!check_if_start_pos(data))
		return (free_data(data), 0);
	return (1);
}