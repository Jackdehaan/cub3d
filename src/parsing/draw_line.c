/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:51:25 by jade-haa          #+#    #+#             */
/*   Updated: 2024/04/05 15:10:29 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
void	dda(t_parsing *data, int X0, int Y0, int X1, int Y1, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	Yinc;
	float	X;
	float	Y;
	int		i;

	(void)color;
	dx = X1 - X0;
	dy = Y1 - Y0;
	if (abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	// float Xinc = dx / (float)steps;
	Yinc = dy / (float)steps;
	X = X0;
	Y = Y0;
	i = 0;
	while (i <= steps)
	{
		if (X0 > 0 && X0 < WIDTH && Y0 > 0 && Y0 < HEIGHT)
		{
			mlx_put_pixel(data->image, round(X), round(Y), 0xFFFFFF);
		}
		Y += Yinc;
		i++;
	}
}

// void	render_cube(t_parsing *data)
// {
// 	double		rayDirX;
// 	double		rayDirY;
// 	double		planeX;
// 	double		planeY;
// 	double		cameraX;
// 	int			x;
// 	int			mapX;
// 	int			mapY;
// 	int			posY;
// 	double		sideDistX;
// 	double		sideDistY;
// 	double		deltaDistX;
// 	double		deltaDistY;
// 	double		posX;
// 	double		dirX;
// 	double		dirY;
// 	double		perpWallDist;
// 	int			stepX;
// 	int			stepY;
// 	int			hit;
// 	int			side;
// 	int			lineHeight;
// 	int			drawStart;
// 	int			drawEnd;
// 	int			color;
// 	int			x0;
// 	int			y0;
// 	int			x1;
// 	int			y1;

// 	posX = data->player_position[1];
// 	posY = data->player_position[0];
// 	dirX = 0, dirY = 0;
// 	planeX = 0, planeY = 0.66;
// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		cameraX = 2 * x / (double)WIDTH - 1;
// 		rayDirX = dirX + planeX * cameraX;
// 		rayDirY = dirY + planeY * cameraX;
// 		mapX = (int)posX;
// 		mapY = (int)posY;
// 		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
// 		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
// 		hit = 0;
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (posX - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
// 		}
// 		while (hit == 0)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if (data->map_flood[mapY][mapX] > 0)
// 				hit = 1;
// 		}
// 		// printf("%d | %d\n", mapY, mapX);
// 		if (side == 0)
// 			perpWallDist = (sideDistX - deltaDistX);
// 		else
// 			perpWallDist = (sideDistY - deltaDistY);
// 		// Calculate height of line to draw on screen
// 		lineHeight = (int)(HEIGHT / perpWallDist);
// 		// calculate lowest and highest pixel to fill in current stripe
// 		drawStart = -lineHeight / 2 + HEIGHT / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		drawEnd = lineHeight / 2 + HEIGHT / 2;
// 		if (drawEnd >= HEIGHT)
// 			drawEnd = HEIGHT - 1;
// 		// if (mapX < data->map_width && mapY < data->map_height && mapY >= 0
// 		// 	&& mapX >= 0)
// 		// {
// 		if (data->map_flood[mapY][mapX] == 0)
// 			color = 0x00FF00;
// 		else if (data->map_flood[mapY][mapX] == 1)
// 			color = 0xFF0000;
// 		// 	break ; // white
// 		// default:
// 		// 	color = 0xFF00FA;
// 		// 	break ; // yellow
// 		// }
// 		// give x and y sides different brightness
// 		// if (side == 1)
// 		// {
// 		// 	color = color / 2;
// 		// }
// 		x0 = x;
// 		y0 = drawStart;
// 		x1 = x;
// 		y1 = drawEnd;
// 		dda(data, x0, y0, x1, y1, 0xFF0000);
// 		x++;
// 	}
// }

void	render_cube(t_parsing *data)
{
	double	rayDirX;
	double	rayDirY;
	double	planeX;
	double	planeY;
	double	cameraX;
	int		x;
	int		mapX;
	int		mapY;
	int		posY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	posX;
	double	dirX;
	double	dirY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		x0;
	int		y0;
	int		x1;
	int		y1;

	posX = data->player_position[1];
	posY = data->player_position[0];
	dirX = data->raycasting->dir_x;
	dirY = data->raycasting->dir_y;
	planeX = data->raycasting->plane_x;
	planeY = data->raycasting->plane_y;	
	printf("%f | %f | %f | %f\n", dirX, dirY, planeX, planeY);
	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		mapX = (int)posX;
		mapY = (int)posY;
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		hit = 0;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map_flood[mapY][mapX] > 0)
				hit = 1;
		}
		// printf("%d | %d\n", mapY, mapX);
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		// Calculate height of line to draw on screen
		lineHeight = (int)(HEIGHT / perpWallDist);
		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		// if (mapX < data->map_width && mapY < data->map_height && mapY >= 0
		// 	&& mapX >= 0)
		// {
		// if (data->map_flood[mapY][mapX] == 0)
		// 	color = 0x00FF00;
		// else if (data->map_flood[mapY][mapX] == 1)
		// 	color = 0xFF0000;
		// 	break ; // white
		// default:
		// 	color = 0xFF00FA;
		// 	break ; // yellow
		// }
		// give x and y sides different brightness
		// if (side == 1)
		// {
		// 	color = color / 2;
		// }
		x0 = x;
		y0 = drawStart;
		x1 = x;
		y1 = drawEnd;
		dda(data, x0, y0, x1, y1, 0xFF0000);
		x++;
	}
}