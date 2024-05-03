/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file_utils2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 16:06:58 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/05/03 13:29:51 by rfinneru      ########   odam.nl         */
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

void	set_data_tex(bool *already_exists, char *str, char **str_data)
{
	if (!*str_data)
		*str_data = skip_spaces(str);
	else
		*already_exists = true;
}

int	set_data(t_parsing *data, TEX_COLOR found, char *str, bool *found_start,
		bool *found_end)
{
	bool	already_exists;

	already_exists = false;
	if (*found_start && !*found_end)
		*found_end = true;
	if (found == NO)
		set_data_tex(&already_exists, str, &data->path_north_tex);
	else if (found == SO)
		set_data_tex(&already_exists, str, &data->path_south_tex);
	else if (found == WE)
		set_data_tex(&already_exists, str, &data->path_west_tex);
	else if (found == EA)
		set_data_tex(&already_exists, str, &data->path_east_tex);
	else if (found == F)
		set_data_tex(&already_exists, str, &data->floor_color);
	else if (found == C)
		set_data_tex(&already_exists, str, &data->ceiling_color);
	if (already_exists)
		return (write(STDERR_FILENO, "Duplicate textures/color\n", 25), 0);
	return (1);
}
