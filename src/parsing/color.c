/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 15:40:02 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/06/07 16:58:38 by rfinneru      ########   odam.nl         */
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

int	color_check(int y, char **color, int *i)
{
	if (y > 4 || ft_atoi(*color) > 255 || ft_atoi(*color) < 0)
		return (ft_free(color), write(STDERR_FILENO,
				"Color RGB range is between 0 and 255\n", 37), 0);
	ft_free(color);
	(*i)++;
	return (1);
}

int	color_valid_check(char *str, int ret)
{
	char	*color;
	int		x;
	int		i;
	int		y;

	i = 0;
	x = -1;
	if (!ret)
		return (ret);
	while (++x < 3)
	{
		y = 0;
		if (!malloc_color(&color, str, i))
			return (0);
		while (str[i] && str[i] != ',')
		{
			while (y == 0 && str[i] == '0')
				i++;
			color[y++] = str[i++];
		}
		color[y] = '\0';
		if (!color_check(y, &color, &i))
			return (0);
	}
	return (1);
}

int	color_missing_check(char *str, int ret)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!ret)
		return (ret);
	if (ft_isalnum(str[i]))
		x++;
	while (str[i])
	{
		if (str[i] == ',' && ft_isalnum(str[i + 1]))
			x++;
		i++;
	}
	if (x != 3)
		return (write(STDERR_FILENO, "Invalid color\n", 14), 0);
	return (1);
}
