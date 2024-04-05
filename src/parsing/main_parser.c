/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 13:45:51 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/04 15:33:58 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int init_mlx(t_parsing *data)
{
	data->window = mlx_init(WIDTH, HEIGHT, "CUBE", true);
	if (!data->window)
		return(0);
	data->image = mlx_new_image(data->window, WIDTH, HEIGHT);
	if (!data->image)
		return(0);
	mlx_image_to_window(data->window, data->image, 18, 18);
	return(1);
}

int	parsing(char *file, t_parsing *data)
{
	data->filename = file;
	if (!filename_check(data))
		return (0);
	if (!open_file(data))
		return (0);
	if (!read_file(data))
		return (0);
	if (!init_mlx(data))
		return(0);
	if (!init_map(data))
		return(0);
	if (!check_map(data))
		return(0);
	
	return (1);
}