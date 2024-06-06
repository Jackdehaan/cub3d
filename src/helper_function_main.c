/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helper_function_main.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 16:57:25 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/06/06 17:44:42 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	roundd(double d)
{
	int		i;
	double	remainder;

	i = (int)d;
	remainder = d - i;
	if (remainder >= 0.5)
	{
		i++;
	}
	return (i);
}

int	is_valid_move(double x, double y, t_parsing *data)
{
	
	if (data->map_width < (x)  || data->map_flood[(int)y][((int)x)] != 0 || data->map_flood[roundd(y)][roundd(x)] != 0)
		return (0);
	if (data->map_height < (y))
		return (0);
	if (y < 1)
		return (0);
	if (x < 1)
		return (0);
	return (1);
}

void	rotate_left(t_parsing *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->raycasting->dir_x;
	data->raycasting->dir_x = data->raycasting->dir_x * cos(-rot_speed)
		- data->raycasting->dir_y * sin(-rot_speed);
	data->raycasting->dir_y = old_dir_x * sin(-rot_speed)
		+ data->raycasting->dir_y * cos(-rot_speed);
	old_plane_x = data->raycasting->plane_x;
	data->raycasting->plane_x = data->raycasting->plane_x * cos(-rot_speed)
		- data->raycasting->plane_y * sin(-rot_speed);
	data->raycasting->plane_y = old_plane_x * sin(-rot_speed)
		+ data->raycasting->plane_y * cos(-rot_speed);
}

void	rotate_right(t_parsing *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->raycasting->dir_x;
	data->raycasting->dir_x = data->raycasting->dir_x * cos(rot_speed)
		- data->raycasting->dir_y * sin(rot_speed);
	data->raycasting->dir_y = old_dir_x * sin(rot_speed)
		+ data->raycasting->dir_y * cos(rot_speed);
	old_plane_x = data->raycasting->plane_x;
	data->raycasting->plane_x = data->raycasting->plane_x * cos(rot_speed)
		- data->raycasting->plane_y * sin(rot_speed);
	data->raycasting->plane_y = old_plane_x * sin(rot_speed)
		+ data->raycasting->plane_y * cos(rot_speed);
}

void	reset_map(t_parsing *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(data->image, x, y, BACKGROUND_COLOR);
			x++;
		}
		y++;
	}
}
