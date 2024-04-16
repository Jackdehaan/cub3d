/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file_utils2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 16:06:58 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/16 16:08:04 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	remove_nl(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == ' ' || str[len
			- 1] == '\t'))
	{
		len--;
	}
	return (len);
}

char	*skip_spaces(char *str)
{
	int	i;
	int	nl;

	i = 0;
	while (str[i] == ' ')
		i++;
	nl = remove_nl(str);
	return (ft_strndup(str + i, nl - i));
}

int	set_data(t_parsing *data, TEX_COLOR found, char *str, bool *found_start,
		bool *found_end)
{
	bool	already_exists;

	if (*found_start && !*found_end)
	{
		*found_end = true;
	}
	already_exists = false;
	if (found == NO)
	{
		if (!data->path_north_tex)
			data->path_north_tex = skip_spaces(str);
		else
			already_exists = true;
	}
	else if (found == SO)
	{
		if (!data->path_south_tex)
			data->path_south_tex = skip_spaces(str);
		else
			already_exists = true;
	}
	else if (found == WE)
	{
		if (!data->path_west_tex)
			data->path_west_tex = skip_spaces(str);
		else
			already_exists = true;
	}
	else if (found == EA)
	{
		if (!data->path_east_tex)
			data->path_east_tex = skip_spaces(str);
		else
			already_exists = true;
	}
	else if (found == F)
	{
		if (!data->floor_color)
			data->floor_color = skip_spaces(str);
		else
			already_exists = true;
	}
	else if (found == C)
	{
		if (!data->ceiling_color)
			data->ceiling_color = skip_spaces(str);
		else
			already_exists = true;
	}
	if (already_exists)
		return (write(STDERR_FILENO, "Duplicate textures/color\n", 25), 0);
	return (1);
}