/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_hex.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 15:28:19 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/05/03 15:12:57 by rfinneru      ########   odam.nl         */
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

int	set_hex_color(char **str, unsigned int *hex, int ret)
{
	char	*r;
	char	*g;
	char	*b;
	int		i;

	i = 0;
	if (!ret)
		return (ret);
	if (!find_rgb_part(*str, &r, &i))
		return (0);
	if (!find_rgb_part(*str, &g, &i))
		return (ft_free(&r), 0);
	if (!find_rgb_part(*str, &b, &i))
		return (ft_free(&r), ft_free(&g), 0);
	ft_free(str);
	*hex = rgb_to_hex(ft_atoi(r), ft_atoi(g), ft_atoi(b));
	free_rgb_parts(&r, &g, &b);
	return (1);
}
