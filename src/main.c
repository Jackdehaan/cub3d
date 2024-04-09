/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:10:48 by rfinneru          #+#    #+#             */
/*   Updated: 2024/04/09 15:10:53 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


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

int	is_valid_move(double x, double y, t_parsing *data)
{
	printf("%d | %d\n", data->map_width, data->map_height);
	if ((int)x < 0 || (int)y < 0 || (int)x >= data->map_width || (int)y >= data->map_height)
	{
				printf("false 1 %f | %f\n", x, y);

		return (0);
	}
	if (data->map_flood[(int)y + MOV_SPEED][(int)x + MOV_SPEED] == 1 || data->map_flood[(int)y][(int)x] == 1 || data->map_flood[(int)(y + MOV_SPEED / 2)][(int)(x + MOV_SPEED / 2)] == 1)
	{
		printf("false 2 %f | %f\n", x, y);
		return (0);
	}
	return (1);
}
// void	move_player(double dir_x, double dir_y, double *player_position,
// 		double step_size, int **map)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = player_position[0] + dir_x * step_size;
// 	new_y = player_position[1] + dir_y * step_size;
// 	if (is_valid_move(new_x, new_y, map))
// 	{
// 		player_position[0] = new_x;
// 		player_position[1] = new_y;
// 	}
// }
double	calculateAngle(double dir_x, double dir_y)
{
	return (atan2(dir_y, dir_x));
}

void	keys_loop(void *param)
{
	t_parsing	*data;
	double		oldDirX;
	double		oldPlaneX;
	int			**map;
	int			y;
	int			x;
	double		new_y;
	double		new_x;
	double		angle;

	new_y = 0;
	new_x = 0;
	// int			newPosX;
	// int			newPosY;
	data = param;
	map = data->map_flood;
	y = data->player_position[0];
	x = data->player_position[1];
	angle = atan2(data->raycasting->dir_y, data->raycasting->dir_x);
	// printf("angle = %f\n", angle);
	if (mlx_is_key_down(data->window, MLX_KEY_ESCAPE))
		mlx_close_window(data->window);
	if (mlx_is_key_down(data->window, MLX_KEY_S))
	{
		new_x = data->player_position[1] - cos(angle) * MOV_SPEED;
		new_y = data->player_position[0] - sin(angle) * MOV_SPEED;
		// x = (int)new_x;
		// y = (int)new_y;
		printf("y == %d | x == %d\n", y, x);
		printf("%f | %f\n", cos(angle) * MOV_SPEED, sin(angle) * MOV_SPEED);
		if (is_valid_move(new_x, new_y, data))
		{
			data->player_position[0] = new_y;
			data->player_position[1] = new_x;
		}
		else
			printf("fout S");
	}
	if (mlx_is_key_down(data->window, MLX_KEY_W))	
	{
		new_x = data->player_position[1] + cos(angle) * MOV_SPEED;
		new_y = data->player_position[0] + sin(angle) * MOV_SPEED;
		// x = (int)new_x;
		// y = (int)new_y;
		if (is_valid_move(new_x, new_y, data))
		{
			data->player_position[1] = new_x;
			data->player_position[0] = new_y;
		}
			else
			printf("fout W");
	}
	if (mlx_is_key_down(data->window, MLX_KEY_D))
	{
		new_x = data->player_position[1] - cos(angle - M_PI / 2) * MOV_SPEED;
		new_y = data->player_position[0] - sin(angle - M_PI / 2) * MOV_SPEED;
		// x = (int)new_x;
		// y = (int)new_y;
		if (is_valid_move(new_x, new_y, data))
		{
			data->player_position[1] = new_x;
			data->player_position[0] = new_y;
		}
			else
			printf("fout D");
	}
	if (mlx_is_key_down(data->window, MLX_KEY_A))
	{
		new_x = data->player_position[1] + cos(angle - M_PI / 2) * MOV_SPEED;
		new_y = data->player_position[0] + sin(angle - M_PI / 2) * MOV_SPEED;
		// x = (int)new_x;
		// y = (int)new_y;
		if (is_valid_move(new_x, new_y, data))
		{
			data->player_position[1] = new_x;
			data->player_position[0] = new_y;
		}
			else
			printf("fout A");
	}
	// printf("%d | %d | %d | %d\n", data->player_position[0],
	// 	data->player_position[1], data->map_height, data->map_width);
	if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
	{
		oldDirX = data->raycasting->dir_x;
		data->raycasting->dir_x = data->raycasting->dir_x * cos(-ROT_SPEED)
			- data->raycasting->dir_y * sin(-ROT_SPEED);
		data->raycasting->dir_y = oldDirX * sin(-ROT_SPEED)
			+ data->raycasting->dir_y * cos(-ROT_SPEED);
		oldPlaneX = data->raycasting->plane_x;
		data->raycasting->plane_x = data->raycasting->plane_x * cos(-ROT_SPEED)
			- data->raycasting->plane_y * sin(-ROT_SPEED);
		data->raycasting->plane_y = oldPlaneX * sin(-ROT_SPEED)
			+ data->raycasting->plane_y * cos(-ROT_SPEED);
	}
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
	{
		oldDirX = data->raycasting->dir_x;
		data->raycasting->dir_x = data->raycasting->dir_x * cos(ROT_SPEED)
			- data->raycasting->dir_y * sin(ROT_SPEED);
		data->raycasting->dir_y = oldDirX * sin(ROT_SPEED)
			+ data->raycasting->dir_y * cos(ROT_SPEED);
		oldPlaneX = data->raycasting->plane_x;
		data->raycasting->plane_x = data->raycasting->plane_x * cos(ROT_SPEED)
			- data->raycasting->plane_y * sin(ROT_SPEED);
		data->raycasting->plane_y = oldPlaneX * sin(ROT_SPEED)
			+ data->raycasting->plane_y * cos(ROT_SPEED);
	}
	// printf("atan == %f |", calculateAngle(data->raycasting->dir_x,
	// 		data->raycasting->dir_y));
	reset_map(data);
	render_cube(data);
}

int	main(int ac, char **av)
{
	static t_parsing	data;

	if (ac == 2)
	{
		if (!parsing(av[1], &data))
			return (1);
		if (!set_ray_struct(&data))
			return (0);
		mlx_loop_hook(data.window, keys_loop, &data);
		mlx_loop(data.window);
		mlx_terminate(data.window);
	}
	else
		return (write(STDERR_FILENO, "usage: ./cub3D *.cub\n", 21), 1);
	return (0);
}

