/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_helper_functions.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 16:08:35 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/06/07 16:10:03 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

struct mlx_texture	*choose_texture(t_parsing *data, double y, double x,
		int side)
{
	(void)data;
	(void)y;
	(void)x;
	if (side == 0)
	{
		if (x > 0)
			return (data->fd_east_tex);
		return (data->fd_west_tex);
	}
	else if (side == 1)
	{
		if (y < 0)
			return (data->fd_north_tex);
		return (data->fd_south_tex);
	}
	return (NULL);
}

void	put_pixels(t_raycasting *values)
{
	int				y;
	u_int32_t		tmp;
	t_raycasting	*v;

	v = values;
	y = v->drawstart;
	while (y < v->drawend)
	{
		v->tex_y = (int)v->texpos & (TEX_HEIGHT - 1);
		v->texpos += v->step;
		if (v->tex_x >= 0 && v->tex_x < TEX_WIDTH && v->tex_y >= 0
			&& v->tex_y < TEX_HEIGHT)
		{
			v->texel_index = (TEX_WIDTH * v->tex_y + v->tex_x) * 4;
			v->red = v->tex->pixels[v->texel_index];
			v->green = v->tex->pixels[v->texel_index + 1];
			v->blue = v->tex->pixels[v->texel_index + 2];
			v->alpha = v->tex->pixels[v->texel_index + 3];
			tmp = (v->red << 24) | (v->green << 16) | (v->blue << 8) | v->alpha;
			v->colors[v->i] = tmp;
		}
		v->i++;
		y++;
	}
}

void	init_values_loop(t_raycasting *values)
{
	values->camera_x = 2 * values->x / (double)WIDTH - 1;
	values->ray_dir_x = values->dir_x + values->plane_x * values->camera_x;
	values->ray_dir_y = values->dir_y + values->plane_y * values->camera_x;
	values->map_x = (int)values->pos_x;
	values->map_y = (int)values->pos_y;
	if (values->ray_dir_x == 0)
		values->delta_dis_x = 1e30;
	else
		values->delta_dis_x = ft_abs_double(1 / values->ray_dir_x);
	if (values->ray_dir_y == 0)
		values->delta_dis_y = 1e30;
	else
		values->delta_dis_y = ft_abs_double(1 / values->ray_dir_y);
	values->hit = 0;
}

void	get_direction(t_raycasting *values)
{
	if (values->ray_dir_x < 0)
	{
		values->stepx = -1;
		values->side_dis_x = (values->pos_x - values->map_x)
			* values->delta_dis_x;
	}
	else
	{
		values->stepx = 1;
		values->side_dis_x = (values->map_x + 1.0 - values->pos_x)
			* values->delta_dis_x;
	}
	if (values->ray_dir_y < 0)
	{
		values->stepy = -1;
		values->side_dis_y = (values->pos_y - values->map_y)
			* values->delta_dis_y;
	}
	else
	{
		values->stepy = 1;
		values->side_dis_y = (values->map_y + 1.0 - values->pos_y)
			* values->delta_dis_y;
	}
}

void	get_wall(t_raycasting *values, t_parsing *data)
{
	while (values->hit == 0)
	{
		if (values->side_dis_x < values->side_dis_y)
		{
			values->side_dis_x += values->delta_dis_x;
			values->map_x += values->stepx;
			values->side = 0;
		}
		else
		{
			values->side_dis_y += values->delta_dis_y;
			values->map_y += values->stepy;
			values->side = 1;
		}
		if (data->map_flood[values->map_y][values->map_x] > 0)
			values->hit = 1;
	}
	if (values->side == 0)
		values->perpwalldist = (values->side_dis_x - values->delta_dis_x);
	else
		values->perpwalldist = (values->side_dis_y - values->delta_dis_y);
}
