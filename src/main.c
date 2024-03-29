/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 12:10:48 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 13:27:32 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strleng(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	filename_check(t_parsing *data)
{
	int		end;
	char	dotcube[] = "buc.";
	int		x;

	x = 0;
	end = ft_strleng(data->filename) - 1;
	while (data->filename[end] == dotcube[x])
	{
		x++;
		end--;
	}
	if (x != 4)
	{
		write(STDERR_FILENO, "Only use .cub files\n", 20);
		return (0);
	}
	else
		return (1);
}

int	parsing(char *map, t_parsing *data)
{
	data->filename = map;
	if (!filename_check(data))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	static t_parsing	data;

	if (ac == 2)
	{
		if (!parsing(av[1], &data))
			return (1);
	}
	else
		return (write(STDERR_FILENO, "usage: ./cub3D *.cub\n", 21), 1);
	return (0);
}
