/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_hex.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 15:28:19 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/16 15:29:04 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	find_rgb_part(char *str, char **part, int *i)
{
	int	x;

	x = *i;
	while (str[x] && str[x] != ',')
		x++;
	*part = (char *)malloc(sizeof(char) * (x + 1));
	if (!*part)
		return (0);
	x = 0;
	while (str[*i] && str[*i] != ',')
	{
		(*part)[x] = str[*i];
		(*i)++;
		x++;
	}
	if (str[*i] == ',')
		(*i)++;
	if (str[*i] == ',')
		return (ft_free(part), write(STDERR_FILENO, "Multiple commas\n", 16),
			0);
	(*part)[x] = '\0';
	return (1);
}

unsigned int	rgb_to_hex(int r, int g, int b)
{
	return (((unsigned int)r << 16) + ((unsigned int)g << 8) + (unsigned int)b);
}

void	free_rgb_parts(char **r, char **g, char **b)
{
	ft_free(r);
	ft_free(g);
	ft_free(b);
}

int	set_hex_color(t_parsing *data, int ret)
{
	char	*r;
	char	*g;
	char	*b;
	int		i;

	i = 0;
	if (!ret)
		return (ret);
	if (!find_rgb_part(data->floor_color, &r, &i))
		return (free_data(data), 0);
	if (!find_rgb_part(data->floor_color, &g, &i))
		return (free_data(data), ft_free(&r), 0);
	if (!find_rgb_part(data->floor_color, &b, &i))
		return (free_data(data), ft_free(&r), ft_free(&g), 0);
	ft_free(&data->floor_color);
	data->hex_floor = rgb_to_hex(ft_atoi(r), ft_atoi(g), ft_atoi(b));
	free_rgb_parts(&r, &g, &b);
	i = 0;
	if (!find_rgb_part(data->ceiling_color, &r, &i))
		return (free_data(data), 0);
	if (!find_rgb_part(data->ceiling_color, &g, &i))
		return (free_data(data), ft_free(&r), 0);
	if (!find_rgb_part(data->ceiling_color, &b, &i))
		return (free_data(data), ft_free(&r), ft_free(&g), 0);
	ft_free(&data->ceiling_color);
	data->hex_ceiling = rgb_to_hex(ft_atoi(r), ft_atoi(g), ft_atoi(b));
	free_rgb_parts(&r, &g, &b);
	return (1);
}
