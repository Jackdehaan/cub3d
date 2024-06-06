/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 11:51:25 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/06/06 18:15:38 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	still_be_named(t_raycasting *values, t_parsing *data)
{
	double	wallx;

	values->lineHeight = (int)(HEIGHT / values->perpWallDist);
	values->drawStart = -values->lineHeight / 2 + HEIGHT / 2 + values->pitch;
	if (values->drawStart < 0)
		values->drawStart = 0;
	values->drawEnd = values->lineHeight / 2 + HEIGHT / 2 + values->pitch;
	if (values->drawEnd >= HEIGHT)
		values->drawEnd = HEIGHT - 1;
	values->texNum = data->map_flood[values->mapY][values->mapX] - 1;
	if (values->side == 0)
		wallx = values->posY + values->perpWallDist * values->rayDirY;
	else
		wallx = values->posX + values->perpWallDist * values->rayDirX;
	wallx -= floor((wallx));
	values->texX = (int)(wallx * (double)TEX_WIDTH);
	if (values->side == 0 && values->rayDirX > 0)
		values->texX = TEX_WIDTH - values->texX - 1;
	if (values->side == 1 && values->rayDirY < 0)
		values->texX = TEX_WIDTH - values->texX - 1;
	values->step = 1.0 * TEX_HEIGHT / values->lineHeight;
	values->texPos = (values->drawStart - values->pitch - HEIGHT / 2
			+ values->lineHeight / 2) * values->step;
}

void	main_loop(t_raycasting *values, t_parsing *data)
{
	int	index;

	index = 0;
	while (values->x < WIDTH)
	{
		init_values_loop(values);
		get_direction(values);
		get_wall(values, data);
		still_be_named(values, data);
		values->i = 0;
		values->tex = choose_texture(data, values->rayDirY, values->rayDirX,
				values->side);
		put_pixels(values);
		values->x0 = values->x;
		values->y0 = values->drawStart;
		values->x1 = values->x;
		values->y1 = values->drawEnd;
		// printf("%d | %d | %d | %d ", values->x0, values->y0, values->x1,
		// values->y1);
		dda(data, values);
		while (index < values->i)
		{
			values->colors[index] = 0;
			index++;
		}
		values->x++;
	}
}

void	render_cube(t_parsing *data)
{
	static t_raycasting	*values;

	values = NULL;
	if (!values)
	{
		values = (t_raycasting *)malloc(sizeof(t_raycasting));
		if (!values)
			return ;
	}
	values->pitch = 100;
	values->posX = data->player_pos[1];
	values->posY = data->player_pos[0];
	values->dirX = data->raycasting->dir_x;
	values->dirY = data->raycasting->dir_y;
	values->planeX = data->raycasting->plane_x;
	values->planeY = data->raycasting->plane_y;
	values->x = 0;
	main_loop(values, data);
}
