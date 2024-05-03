/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:51:25 by jade-haa          #+#    #+#             */
/*   Updated: 2024/04/12 17:52:45 by jade-haa         ###   ########.fr       */
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
			return(data->fd_east_tex);
		return (data->fd_west_tex);
	}
	else if (side == 1)
	{
		if (y < 0)
			return (data->fd_north_tex);
		return (data->fd_south_tex);
	}
	return(NULL);
}

void	dda(t_parsing *data, int X0, int Y0, int X1, int Y1, u_int32_t *colors)
{
	int		dx;
	int		dy;
	int		steps;
	float	Yinc;
	float	X;
	float	Y;
	int		i;
	int		extra;
	int		y_begin;
	int		x_begin;
	int		test;

	y_begin = 0;
	x_begin = 0;
	extra = 0;
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
	test = 0;
	x_begin = X0;
	while (test < Y0)
	{
		if (X0 > 0 && X0 < WIDTH && Y0 > 0 && Y0 < HEIGHT)
		{
			mlx_put_pixel(data->image, round(x_begin), round(y_begin),
				data->hex_ceiling);
		}
		y_begin++;
		test++;
	}
	test = Y1;
	y_begin = Y1;
	while (test < HEIGHT)
	{
		if (X0 > 0 && X0 < WIDTH && Y0 > 0 && Y0 < HEIGHT)
		{
			mlx_put_pixel(data->image, round(x_begin), round(y_begin),
				data->hex_floor);
		}
		y_begin++;
		test++;
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
			mlx_put_pixel(data->image, round(X), round(Y), colors[extra]);
			extra++;
		}
		// else
		// 	mlx_put_pixel(data->image, round(X), round(Y), 0xFF00FF);
		Y += Yinc;
		i++;
	}
}

void	render_cube(t_parsing *data)
{
	double				rayDirX;
	double				rayDirY;
	double				planeX;
	double				planeY;
	double				cameraX;
	int					x;
	int					mapX;
	int					mapY;
	double				posY;
	double				sideDistX;
	double				sideDistY;
	double				deltaDistX;
	double				deltaDistY;
	double				posX;
	double				dirX;
	double				dirY;
	double				perpWallDist;
	int					stepX;
	int					stepY;
	int					hit;
	int					side;
	int					lineHeight;
	int					drawStart;
	int					drawEnd;
	int					x0;
	int					y0;
	int					x1;
	int					texNum;
	u_int32_t			colors[5000];
	int					y1;
	int					pitch;
	int					i;
	int					texX;
	double				step;
	double				texPos;
	int					texY;
	struct mlx_texture	*tex;
	int					texelIndex;
	uint8_t				red;
	uint8_t				green;
	uint8_t				blue;
	uint8_t				alpha;

	pitch = 100;
	posX = data->player_position[1];
	posY = data->player_position[0];
	// printf("y pos == %f | x pos == %f\n", data->player_position[0],
	// data->player_position[1]);
	// printf("current object %d\n", data->map_flood[(int)posY][(int)posX]);
	dirX = data->raycasting->dir_x;
	dirY = data->raycasting->dir_y;
	planeX = data->raycasting->plane_x;
	planeY = data->raycasting->plane_y;
	// printf("%f | %f | %f | %f | %d | %f\n", dirX, dirY, planeX, planeY, posY,
	// posX);
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
		// printf("%f | %f\n", rayDirY, rayDirX);
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
		drawStart = -lineHeight / 2 + HEIGHT / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2 + pitch;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		texNum = data->map_flood[mapY][mapX] - 1;
		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		texX = (int)(wallX * (double)TEX_WIDTH);
		if (side == 0 && rayDirX > 0)
			texX = TEX_WIDTH - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEX_WIDTH - texX - 1;
		step = 1.0 * TEX_HEIGHT / lineHeight;
		// Starting texture coordinate
		texPos = (drawStart - pitch - HEIGHT / 2 + lineHeight / 2) * step;
		i = 0;
		// for (int iets = 0; iets < drawStart; iets++)
		// {
		// 	colors[i] =  0x1100FFFF;
		// 	i++;
		// }
		// printf("i == %d\n", i);
		tex = choose_texture(data, rayDirY, rayDirX, side);
		// printf("%d | %d\n",rayDirY, rayDirX);
		for (int y = drawStart; y < drawEnd; y++)
		{
			texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step;
			if (texX >= 0 && texX < TEX_WIDTH && texY >= 0 && texY < TEX_HEIGHT)
			{
				texelIndex = (TEX_WIDTH * texY + texX) * 4;
				// Multiply by 4 for 4-byte texels (RGBA format)
				// Retrieve the texel from the texture array
				red = tex->pixels[texelIndex];
				green = tex->pixels[texelIndex + 1];
				blue = tex->pixels[texelIndex + 2];
				alpha = tex->pixels[texelIndex + 3];
				// Combine the color components into a single 4-byte color value
				colors[i] = (red << 24) | (green << 16) | (blue << 8) | alpha;
				// colors[i] = (alpha << 24) | (red << 16) | (green << 8) | blue;
				// printf("%d | %d totaal index %d\n", colors[i],
				// data-wh
			}
			// else
			// {
			// 	// Handle out-of-bounds texture coordinates
			// 	// printf("else statement\n");
			// 	colors[i] = 0xFF00FF00;
			// }
			i++;
		}
		// for (int iets = drawEnd; iets < HEIGHT; iets++)
		// {
		// 	colors[i] =  0xFF00FFFF;
		// 	i++;
		// }
		// printf("text %d | %d\n", data->fd_east_tex->height,
		// 	data->fd_east_tex->width);
		// for (size_t size = 0; size < 4096; size++)
		// {
		// 	printf("%hhu ", data->fd_east_tex->pixels[size]);
		// 	if (size % 64 == 0)
		// 		printf("\n");
		// }
		// exit(EXIT_FAILURE);
		x0 = x;
		y0 = drawStart;
		x1 = x;
		y1 = drawEnd;
		// printf("%d | %d | %d | %d\n", x0, x1, y0, y1);
		dda(data, x0, y0, x1, y1, colors);
		for (int index = 0; index < i; index++)
		{
			colors[index] = 0;
		}
		x++;
	}
	// exit(EXIT_FAILURE);
}
