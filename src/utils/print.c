/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 16:58:32 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/04 14:42:05 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_tex_color(t_parsing *data)
{
	printf("%s\n", data->path_north_tex);
	printf("%s\n", data->path_south_tex);
	printf("%s\n", data->path_west_tex);
	printf("%s\n", data->path_east_tex);
	printf("%s\n", data->floor_color);
	printf("%s\n", data->ceiling_color);
}