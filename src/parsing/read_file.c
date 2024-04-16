/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 13:53:36 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/16 16:07:19 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/get_next_line.h"

int	gnl_to_map(char *gnl_output, t_parsing *data, bool *found_start,
		bool *found_end)
{
	char	*trim;

	trim = trim_spaces_from_end(gnl_output, data);
	if (trim)
	{
		if (*found_end)
		{
			ft_free(&gnl_output);
			free_data(data);
			ft_free(&trim);
			write(STDERR_FILENO, "Found empty line in map\n", 24);
			exit(EXIT_FAILURE);
		}
		*found_start = true;
	}
	else if (*found_start)
	{
		*found_end = true;
		return (1);
	}
	data->map = ft_strjoin_gnl(data->map, trim);
	ft_free(&trim);
	return (1);
}

int	read_file(t_parsing *data)
{
	char		*gnl_output;
	static bool	found_start;
	static bool	found_end;

	gnl_output = NULL;
	data->map = ft_strdup("");
	if (!data->map)
		return (0);
	while (1)
	{
		gnl_output = get_next_line(data->file_fd);
		if (!gnl_output)
			break ;
		if (!check_if_tex_color(data, gnl_output, &found_start, &found_end))
			return (free_data(data), ft_free(&gnl_output), 0);
		if (check_if_tex_color_return(gnl_output))
			if (!gnl_to_map(gnl_output, data, &found_start, &found_end))
				return (0);
		ft_free(&gnl_output);
	}
	close(data->file_fd);
	data->file_fd = -1;
	ft_free(&gnl_output);
	if (!tex_color_filled(data))
		return (free_data(data), 0);
	print_tex_color(data);
	// printf("data->map \n%s\n", data->map);
	return (1);
}
