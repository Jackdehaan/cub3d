/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 13:53:36 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/05/03 15:28:50 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/get_next_line.h"

int	gnl_to_map(char *gnl_output, t_parsing *data)
{
	char	*trimmed_line;

	trimmed_line = trim_spaces_from_end(gnl_output, data);
	if (trimmed_line)
	{
		if (data->found_end)
		{
			ft_free(&gnl_output);
			free_data(data);
			ft_free(&trimmed_line);
			write(STDERR_FILENO, "Found empty line in map\n", 24);
			exit(EXIT_FAILURE);
		}
		data->found_start = true;
	}
	else if (data->found_start)
	{
		data->found_end = true;
		return (1);
	}
	data->map = ft_strjoin_gnl(data->map, trimmed_line);
	ft_free(&trimmed_line);
	return (1);
}

int	read_file(t_parsing *data)
{
	char	*gnl_output;

	gnl_output = NULL;
	data->map = ft_strdup("");
	if (!data->map)
		return (0);
	while (1)
	{
		gnl_output = get_next_line(data->file_fd);
		if (!gnl_output)
			break ;
		if (!check_if_tex_color(data, gnl_output))
			return (free_data(data), ft_free(&gnl_output), 0);
		if (check_if_tex_color_return(gnl_output))
			if (!gnl_to_map(gnl_output, data))
				return (0);
		ft_free(&gnl_output);
	}
	close(data->file_fd);
	data->file_fd = -1;
	if (!tex_color_filled(data))
		return (ft_free(&gnl_output), free_data(data), 0);
	return (ft_free(&gnl_output), 1);
}
