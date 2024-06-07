/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 16:02:25 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/06/07 17:21:09 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/get_next_line.h"

int	find_no_space(char **str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while ((*str)[i])
	{
		if (!ft_isdigit((*str)[i]) && (*str)[i] != ',' && (*str)[i] != ' ')
			return (write(STDERR_FILENO, "Non-digit symbol found in color\n",
					32), -1);
		if ((*str)[i] != ' ')
			x++;
		i++;
	}
	return (x);
}

int	remove_whitespace(char **str, int ret)
{
	int		i;
	int		x;
	char	*tmp;

	i = 0;
	if (!ret)
		return (ret);
	if (!ft_isdigit((*str)[i]) && (*str)[i] != ' ')
		return (write(STDERR_FILENO,
				"Found comma/invalid character at the start\n", 43), 0);
	x = find_no_space(str);
	if (x == -1)
		return (0);
	tmp = (char *)malloc((x + 1) * sizeof(char));
	if (!tmp)
		return (0);
	i = -1;
	x = 0;
	while ((*str)[++i])
		if ((*str)[i] != ' ')
			tmp[x++] = (*str)[i];
	tmp[x] = '\0';
	ft_free(str);
	*str = tmp;
	return (1);
}

void	empty_check(t_parsing *data, int *ret)
{
	if (!data->path_north_tex)
		*ret = 0;
	if (!data->path_south_tex)
		*ret = 0;
	if (!data->path_west_tex)
		*ret = 0;
	if (!data->path_east_tex)
		*ret = 0;
	if (!data->floor_color)
		*ret = 0;
	if (!data->ceiling_color)
		*ret = 0;
	if (*ret == 0)
		write(STDERR_FILENO, "Textures or colors not filled\n", 30);
}

int	t_tex_color_filled(t_parsing *data)
{
	int	ret;

	ret = 1;
	empty_check(data, &ret);
	if (ret == 1)
	{
		ret = remove_whitespace(&data->ceiling_color, ret);
		ret = remove_whitespace(&data->floor_color, ret);
		ret = color_missing_check(data->ceiling_color, ret);
		ret = color_missing_check(data->floor_color, ret);
		ret = color_valid_check(data->ceiling_color, ret);
		ret = color_valid_check(data->floor_color, ret);
		ret = set_hex_color(&data->floor_color, &data->hex_floor, ret);
		ret = set_hex_color(&data->ceiling_color, &data->hex_ceiling, ret);
		ret = check_tex_path(data, ret);
	}
	return (ret);
}

char	*trim_spaces_from_end(char *line, t_parsing *data)
{
	char	*trimmed;
	int		i;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (map_char(line[i]))
			break ;
		if (!map_char(line[i]) && line[i] != ' ' && line[i] != '\n')
		{
			write(STDERR_FILENO, "Found a non-map character in your map.\n",
				39);
			ft_free(&line);
			free_data(data);
			exit(EXIT_FAILURE);
		}
		i--;
	}
	if (i == -1)
		return (NULL);
	trimmed = ft_strndup(line, i + 1);
	if (!trimmed)
		return (NULL);
	trimmed = ft_strjoin_gnl(trimmed, "\n");
	return (trimmed);
}
