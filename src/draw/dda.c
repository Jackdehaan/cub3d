/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 16:02:59 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/06/06 18:13:28 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_floor_celling(t_parsing *data, t_raycasting *values,
		t_dda *points)
{
	while (points->index < values->y0)
	{
		if (values->x0 > 0 && values->x0 < WIDTH && values->y0 > 0
			&& values->y0 < HEIGHT)
			mlx_put_pixel(data->image, round(points->x_begin),
				round(points->y_begin), data->hex_ceiling);
		points->y_begin++;
		points->index++;
	}
	points->index = values->y1;
	points->y_begin = values->y1;
	while (points->index < HEIGHT)
	{
		if (values->x0 > 0 && values->x0 < WIDTH && values->y0 > 0
			&& values->y0 < HEIGHT)
			mlx_put_pixel(data->image, round(points->x_begin),
				round(points->y_begin), data->hex_floor);
		points->y_begin++;
		points->index++;
	}
}

void	render_walls(t_parsing *data, t_raycasting *values, t_dda *points)
{
	points->Yinc = points->dy / (float)points->steps;
	points->X = values->x0;
	points->Y = values->y0;
	points->i = 0;
	while (points->i <= points->steps)
	{
		if (values->x0 > 0 && values->x0 < WIDTH && values->y0 > 0
			&& values->y0 < HEIGHT)
		{
			mlx_put_pixel(data->image, round(points->X), round(points->Y),
				values->colors[points->extra]);
			points->extra++;
		}
		points->Y += points->Yinc;
		points->i++;
	}
}

void	dda(t_parsing *data, t_raycasting *values)
{
	static t_dda	*points;

	if (!points)
	{
		points = (t_dda *)malloc(sizeof(t_dda));
		if (!points)
			return ;
	}
	points->y_begin = 0;
	points->x_begin = 0;
	points->extra = 0;
	points->dx = values->x1 - values->x0;
	points->dy = values->y1 - values->y0;
	if (abs(points->dx) > abs(points->dy))
		points->steps = abs(points->dx);
	else
		points->steps = abs(points->dy);
	points->index = 0;
	points->x_begin = values->x0;
	render_floor_celling(data, values, points);
	render_walls(data, values, points);
}
