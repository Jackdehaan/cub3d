/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 13:53:36 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 17:23:24 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/get_next_line.h"

int	set_data(t_parsing *data, TEX_COLOR found, char *str)
{
	bool	already_exists;

	already_exists = false;
	if (found == NO)
	{
		if (!data->path_north_tex)
			data->path_north_tex = ft_strndup(str, ft_strlen(str) - 1);
		else
			already_exists = true;
	}
	else if (found == SO)
	{
		if (!data->path_south_tex)
			data->path_south_tex = ft_strndup(str, ft_strlen(str) - 1);
		else
			already_exists = true;
	}
	else if (found == WE)
	{
		if (!data->path_west_tex)
			data->path_west_tex = ft_strndup(str, ft_strlen(str) - 1);
		else
			already_exists = true;
	}
	else if (found == EA)
	{
		if (!data->path_east_tex)
			data->path_east_tex = ft_strndup(str, ft_strlen(str) - 1);
		else
			already_exists = true;
	}
	else if (found == F)
	{
		if (!data->floor_color)
			data->floor_color = ft_strndup(str, ft_strlen(str) - 1);
		else
			already_exists = true;
	}
	else if (found == C)
	{
		if (!data->ceiling_color)
			data->ceiling_color = ft_strndup(str, ft_strlen(str) - 1);
		else
			already_exists = true;
	}
	if (already_exists)
		return (write(STDERR_FILENO, "Duplicate textures/color\n", 25), 0);
	return (1);
}

int	check_if_tex_color(t_parsing *data, char *str)
{
	int	ret_value;

	ret_value = 1;
	if (!ft_strncmp(str, "NO ", 3))
		ret_value = set_data(data, NO, str + 3);
	else if (!ft_strncmp(str, "SO ", 3))
		ret_value = set_data(data, SO, str + 3);
	else if (!ft_strncmp(str, "WE ", 3))
		ret_value = set_data(data, WE, str + 3);
	else if (!ft_strncmp(str, "EA ", 3))
		ret_value = set_data(data, EA, str + 3);
	else if (!ft_strncmp(str, "F ", 2))
		ret_value = set_data(data, F, str + 2);
	else if (!ft_strncmp(str, "C ", 2))
		ret_value = set_data(data, C, str + 2);
	return (ret_value);
}

int	check_if_tex_color_return(char *str)
{
	int	ret_value;

	ret_value = 1;
	if (!ft_strncmp(str, "NO ", 3))
		ret_value = 0;
	else if (!ft_strncmp(str, "SO ", 3))
		ret_value = 0;
	else if (!ft_strncmp(str, "WE ", 3))
		ret_value = 0;
	else if (!ft_strncmp(str, "EA ", 3))
		ret_value = 0;
	else if (!ft_strncmp(str, "F ", 2))
		ret_value = 0;
	else if (!ft_strncmp(str, "C ", 2))
		ret_value = 0;
	return (ret_value);
}

int	tex_color_filled(t_parsing *data)
{
	int	ret;

	ret = 1;
	if (!data->path_north_tex)
		ret = 0;
	if (!data->path_south_tex)
		ret = 0;
	if (!data->path_west_tex)
		ret = 0;
	if (!data->path_east_tex)
		ret = 0;
	if (!data->floor_color)
		ret = 0;
	if (!data->ceiling_color)
		ret = 0;
	if (ret == 0)
		write(STDERR_FILENO, "Textures or color not filled\n", 29);
	return (ret);
}

int	read_file(t_parsing *data)
{
	char *gnl_output;
	gnl_output = NULL;
	data->map = ft_strdup("");
	while (1)
	{
		gnl_output = get_next_line(data->file_fd);
		if (!gnl_output)
			break ;
		if (!check_if_tex_color(data, gnl_output))
			return (ft_free(&gnl_output), 0);
		if (check_if_tex_color_return(gnl_output))
			data->map = ft_strjoin_gnl(data->map, gnl_output);
		ft_free(&gnl_output);
	}
	ft_free(&gnl_output);
	if (!tex_color_filled(data))
		return (0);
	print_tex_color(data);
	printf("data->map \n%s\n", data->map);
	return (1);
}