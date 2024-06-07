/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 14:01:04 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/06/07 16:14:59 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/get_next_line.h"

void	ft_free(char **buffer)
{
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
}

void	clean_gnl(int file_fd)
{
	char	*line;

	if (file_fd == -1)
		return ;
	while (1)
	{
		line = get_next_line(file_fd);
		if (!line)
			break ;
		ft_free(&line);
	}
	close(file_fd);
}

void	free_map_flood(t_parsing *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		if (data->map_flood[i])
			free(data->map_flood[i]);
		i++;
	}
	if (data->map_flood)
		free(data->map_flood);
}

void	free_textures(t_parsing *data)
{
	if (data->fd_north_tex)
		mlx_delete_texture(data->fd_north_tex);
	if (data->fd_south_tex)
		mlx_delete_texture(data->fd_south_tex);
	if (data->fd_east_tex)
		mlx_delete_texture(data->fd_east_tex);
	if (data->fd_west_tex)
		mlx_delete_texture(data->fd_west_tex);
}

void	free_data(t_parsing *data)
{
	clean_gnl(data->file_fd);
	if (data->map)
		ft_free(&data->map);
	if (data->path_north_tex)
		ft_free(&data->path_north_tex);
	if (data->path_east_tex)
		ft_free(&data->path_east_tex);
	if (data->path_west_tex)
		ft_free(&data->path_west_tex);
	if (data->path_south_tex)
		ft_free(&data->path_south_tex);
	if (data->floor_color)
		ft_free(&data->floor_color);
	if (data->ceiling_color)
		ft_free(&data->ceiling_color);
	if (data->map_flood)
		free_map_flood(data);
	free_textures(data);
	free(data->dda_values);
}
