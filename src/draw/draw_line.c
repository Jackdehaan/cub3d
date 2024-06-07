/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 11:51:25 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/06/07 16:02:17 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	still_be_named(t_raycasting *values, t_parsing *data)
{
	double	wallx;

	values->lineheight = (int)(HEIGHT / values->perpwalldist);
	values->drawstart = -values->lineheight / 2 + HEIGHT / 2 + values->pitch;
	if (values->drawstart < 0)
		values->drawstart = 0;
	values->drawend = values->lineheight / 2 + HEIGHT / 2 + values->pitch;
	if (values->drawend >= HEIGHT)
		values->drawend = HEIGHT - 1;
	values->texnum = data->map_flood[values->map_y][values->map_x] - 1;
	if (values->side == 0)
		wallx = values->pos_y + values->perpwalldist * values->ray_dir_y;
	else
		wallx = values->pos_x + values->perpwalldist * values->ray_dir_x;
	wallx -= floor((wallx));
	values->tex_x = (int)(wallx * (double)TEX_WIDTH);
	if (values->side == 0 && values->ray_dir_x > 0)
		values->tex_x = TEX_WIDTH - values->tex_x - 1;
	if (values->side == 1 && values->ray_dir_y < 0)
		values->tex_x = TEX_WIDTH - values->tex_x - 1;
	values->step = 1.0 * TEX_HEIGHT / values->lineheight;
	values->texpos = (values->drawstart - values->pitch - HEIGHT / 2
			+ values->lineheight / 2) * values->step;
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
		values->tex = choose_texture(data, values->ray_dir_y, values->ray_dir_x,
				values->side);
		put_pixels(values);
		values->x0 = values->x;
		values->y0 = values->drawstart;
		values->x1 = values->x;
		values->y1 = values->drawend;
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
	t_raycasting	*values;

	values = data->dda_values;
	values->pitch = 100;
	values->pos_x = data->player_pos[1];
	values->pos_y = data->player_pos[0];
	values->dir_x = data->raycasting->dir_x;
	values->dir_y = data->raycasting->dir_y;
	values->plane_x = data->raycasting->plane_x;
	values->plane_y = data->raycasting->plane_y;
	values->x = 0;
	main_loop(values, data);
}
