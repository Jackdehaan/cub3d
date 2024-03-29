/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 12:10:48 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 13:46:13 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
