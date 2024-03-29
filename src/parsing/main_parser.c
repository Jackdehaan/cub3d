/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 13:45:51 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 13:53:16 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parsing(char *file, t_parsing *data)
{
	data->filename = file;
	if (!filename_check(data))
		return (0);
	if (!open_file(data))
		return (0);
	if (!set_textures_and_colors(data))
		return (0);
	return (1);
}