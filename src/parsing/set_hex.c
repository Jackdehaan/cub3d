/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_hex.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 15:28:19 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/06/07 18:22:05 by rfinneru      ########   odam.nl         */
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

uint32_t	compute_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	free_rgb_parts(char **r, char **g, char **b)
{
	ft_free(r);
	ft_free(g);
	ft_free(b);
}

int	set_hex_color(char **str, uint32_t *hex, int ret)
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
	*hex = compute_color(ft_atoi(r), ft_atoi(g), ft_atoi(b), 255);
	free_rgb_parts(&r, &g, &b);
	return (1);
}
