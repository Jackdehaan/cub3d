/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 15:40:02 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/16 15:59:33 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	malloc_color(char **color, char *str, int i)
{
	int	y;

	y = 0;
	while (str[i] && str[i] != ',')
	{
		if (y == 0 && str[i] == '0')
		{
			i++;
			continue ;
		}
		y++;
		i++;
	}
	*color = (char *)malloc(sizeof(char) * (y + 1));
	if (!*color)
		return (0);
	return (1);
}

int	color_valid_check(char *str, int ret)
{
	int		x;
	char	*color;
	int		i;
	int		y;

	y = 0;
	i = 0;
	x = 0;
	if (!ret)
		return (0);
	while (x < 3)
	{
		malloc_color(&color, str, i);
		y = 0;
		while (str[i] && str[i] != ',')
		{
			if (y == 0 && str[i] == '0')
			{
				i++;
				continue ;
			}
			color[y] = str[i];
			y++;
			i++;
		}
		color[y] = '\0';
		if (y > 4 || ft_atoi(color) > 255 || ft_atoi(color) < 0)
			return (ft_free(&color), write(STDERR_FILENO,
					"Color RGB range is between 0 and 255\n", 37), 0);
		ft_free(&color);
		i++;
		x++;
	}
	return (1);
}

int	color_missing_check(t_parsing *data, int ret)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!ret)
		return (0);
	if (ft_isalnum(data->floor_color[i]))
		x++;
	while (data->floor_color[i])
	{
		if (data->floor_color[i] == ',' && ft_isalnum(data->floor_color[i + 1]))
			x++;
		i++;
	}
	if (x != 3)
		return (write(STDERR_FILENO, "Invalid color\n", 14), 0);
	i = 0;
	x = 0;
	if (ft_isalnum(data->ceiling_color[i]))
		x++;
	while (data->ceiling_color[i])
	{
		if (data->ceiling_color[i] == ',' && ft_isalnum(data->ceiling_color[i
				+ 1]))
			x++;
		i++;
	}
	if (x != 3)
		return (write(STDERR_FILENO, "Invalid color\n", 14), 0);
	return (1);
}
