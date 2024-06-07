/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_tex.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 16:03:52 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/06/07 16:04:55 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_if_t_tex_color(t_parsing *data, char *str)
{
	int		ret_value;
	char	*no_spaces_str;

	ret_value = 1;
	no_spaces_str = skip_spaces(str);
	if (!no_spaces_str)
		return (0);
	if (!ft_strncmp(no_spaces_str, "NO ", 3))
		ret_value = set_data(data, NO, no_spaces_str + 3);
	else if (!ft_strncmp(no_spaces_str, "SO ", 3))
		ret_value = set_data(data, SO, no_spaces_str + 3);
	else if (!ft_strncmp(no_spaces_str, "WE ", 3))
		ret_value = set_data(data, WE, no_spaces_str + 3);
	else if (!ft_strncmp(no_spaces_str, "EA ", 3))
		ret_value = set_data(data, EA, no_spaces_str + 3);
	else if (!ft_strncmp(no_spaces_str, "F ", 2))
		ret_value = set_data(data, F, no_spaces_str + 2);
	else if (!ft_strncmp(no_spaces_str, "C ", 2))
		ret_value = set_data(data, C, no_spaces_str + 2);
	return (ft_free(&no_spaces_str), ret_value);
}

int	check_if_t_tex_color_return(char *str)
{
	int		ret_value;
	char	*no_spaces_str;

	ret_value = 1;
	no_spaces_str = skip_spaces(str);
	if (!str)
		return (0);
	if (!ft_strncmp(no_spaces_str, "NO ", 3))
		ret_value = 0;
	else if (!ft_strncmp(no_spaces_str, "SO ", 3))
		ret_value = 0;
	else if (!ft_strncmp(no_spaces_str, "WE ", 3))
		ret_value = 0;
	else if (!ft_strncmp(no_spaces_str, "EA ", 3))
		ret_value = 0;
	else if (!ft_strncmp(no_spaces_str, "F ", 2))
		ret_value = 0;
	else if (!ft_strncmp(no_spaces_str, "C ", 2))
		ret_value = 0;
	ft_free(&no_spaces_str);
	return (ret_value);
}

int	png_file_check(char *str, mlx_texture_t **tex)
{
	int		end;
	char	*dotpng;
	int		x;

	x = 0;
	end = ft_strlen(str) - 1;
	dotpng = ft_strdup("gnp.");
	if (!dotpng)
		return (0);
	while (str[end] == dotpng[x])
	{
		x++;
		end--;
	}
	if (x != 4)
		return (ft_free(&dotpng), write(STDERR_FILENO,
				"One or more textures aren't .png files\n", 39), 0);
	else
	{
		*tex = mlx_load_png(str);
		if (!*tex)
			return (ft_free(&dotpng), write(STDERR_FILENO,
					"One of the textures is invalid\n", 31), 0);
		return (ft_free(&dotpng), 1);
	}
}

int	check_tex_path(t_parsing *data, int ret)
{
	if (!ret)
		return (0);
	if (!png_file_check(data->path_north_tex, &data->fd_north_tex))
		return (0);
	if (!png_file_check(data->path_south_tex, &data->fd_south_tex))
		return (0);
	if (!png_file_check(data->path_east_tex, &data->fd_east_tex))
		return (0);
	if (!png_file_check(data->path_west_tex, &data->fd_west_tex))
		return (0);
	return (1);
}
