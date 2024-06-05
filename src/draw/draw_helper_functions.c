/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helper_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:35 by jade-haa          #+#    #+#             */
/*   Updated: 2024/06/05 16:51:06 by jade-haa         ###   ########.fr       */
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
	int			y;
	u_int32_t	tmp;

	y = values->drawStart;
	while (y < values->drawEnd)
	{
		values->texY = (int)values->texPos & (TEX_HEIGHT - 1);
		values->texPos += values->step;
		if (values->texX >= 0 && values->texX < TEX_WIDTH && values->texY >= 0
			&& values->texY < TEX_HEIGHT)
		{
			values->texelIndex = (TEX_WIDTH * values->texY + values->texX) * 4;
			values->red = values->tex->pixels[values->texelIndex];
			values->green = values->tex->pixels[values->texelIndex + 1];
			values->blue = values->tex->pixels[values->texelIndex + 2];
			values->alpha = values->tex->pixels[values->texelIndex + 3];
			tmp = (values->red << 24) | (values->green << 16) | (values->blue << 8) | values->alpha;
			values->colors[values->i] = tmp;
		}
		values->i++;
		y++;
	}
}

void	init_values_loop(t_raycasting *values)
{
	values->cameraX = 2 * values->x / (double)WIDTH - 1;
	values->rayDirX = values->dirX + values->planeX * values->cameraX;
	values->rayDirY = values->dirY + values->planeY * values->cameraX;
	values->mapX = (int)values->posX;
	values->mapY = (int)values->posY;
	if (values->rayDirX == 0)
		values->deltaDistX = 1e30;
	else
		values->deltaDistX = fabs(1 / values->rayDirX);
	if (values->rayDirY == 0)
		values->deltaDistY = 1e30;
	else
		values->deltaDistY = fabs(1 / values->rayDirY);
	values->hit = 0;
}

void	get_direction(t_raycasting *values)
{
	if (values->rayDirX < 0)
	{
		values->stepX = -1;
		values->sideDistX = (values->posX - values->mapX) * values->deltaDistX;
	}
	else
	{
		values->stepX = 1;
		values->sideDistX = (values->mapX + 1.0 - values->posX)
			* values->deltaDistX;
	}
	if (values->rayDirY < 0)
	{
		values->stepY = -1;
		values->sideDistY = (values->posY - values->mapY) * values->deltaDistY;
	}
	else
	{
		values->stepY = 1;
		values->sideDistY = (values->mapY + 1.0 - values->posY)
			* values->deltaDistY;
	}
}

void	get_wall(t_raycasting *values, t_parsing *data)
{
	while (values->hit == 0)
	{
		if (values->sideDistX < values->sideDistY)
		{
			values->sideDistX += values->deltaDistX;
			values->mapX += values->stepX;
			values->side = 0;
		}
		else
		{
			values->sideDistY += values->deltaDistY;
			values->mapY += values->stepY;
			values->side = 1;
		}
		if (data->map_flood[values->mapY][values->mapX] > 0)
			values->hit = 1;
	}
	if (values->side == 0)
		values->perpWallDist = (values->sideDistX - values->deltaDistX);
	else
		values->perpWallDist = (values->sideDistY - values->deltaDistY);
}
