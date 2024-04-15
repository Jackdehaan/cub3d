/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 12:10:48 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/15 15:45:52 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_move(double x, double y, t_parsing *data)
{
	printf("%f | %f | %d | %d\n", x, y, data->map_width, data->map_height);
	if ((int)x - 1 <= 0 || (int)y - 1 <= 0 || (int)x + 1 >= data->map_width - 2
		|| (int)y + 1 >= data->map_height - 2)
	{
		printf("false 1 %f | %f\n", x, y);
		return (0);
	}
	if (data->map_flood[(int)y][(int)x] == 1)
		return (write(1, "1", 1), 0);
	if (data->map_flood[(int)(y + (MOV_SPEED * 2))][(int)x] == 1)
		return (write(1, "2", 1), 0);
	if (data->map_flood[(int)y][(int)(x + (MOV_SPEED * 2))] == 1)
		return (write(1, "3", 1), 0);
	if (data->map_flood[(int)(y + (MOV_SPEED * 2))][(int)(x + (MOV_SPEED
				* 2))] == 1)
		return (write(1, "4", 1), 0);
	if (data->map_flood[(int)(y - (MOV_SPEED))][(int)(x - (MOV_SPEED))] == 1)
		return (write(1, "5", 1), 0);
	if (data->map_flood[(int)(y - (MOV_SPEED))][(int)((x) - (MOV_SPEED))] == 1)
		return (write(1, "6", 1), 0);
	if (data->map_flood[(int)((y) - (MOV_SPEED))][(int)(x - (MOV_SPEED))] == 1)
		return (write(1, "7", 1), 0);
	// if (data->map_flood[(int)((y + 1) - (MOV_SPEED * 3))][(int)((x + 1)
	// 		- (MOV_SPEED * 4))] == 1)
	// 	return (write(1, "8", 1), 0);
	// if (data->map_flood[(int)y][(int)(x + (MOV_SPEED * 2))] == 1)
	// 	return (write(1, "5", 1), 0);
	if (data->map_flood[(int)y][(int)x] == 1)
		return (write(1, "8", 1), 0);
	// if (data->map_flood[(int)round((y) + MOV_SPEED)][(int)round((x)
	// 		+ MOV_SPEED)] == 1 || data->map_flood[(int)round((y + 0.5)
	// 		+ MOV_SPEED)][(int)round((x + 0.5))] || data->map_flood[(int)round(y
	// 		+ MOV_SPEED / 2)][(int)round(x + MOV_SPEED / 2)] == 1
	// 	|| data->map_flood[(int)round(y + MOV_SPEED * 2)][(int)round(x
	// 		+ (MOV_SPEED * 2))] == 1)
	// {
	// 	printf("false 2 %f | %f\n", x, y);
	// 	printf("block %d\n", data->map_flood[(int)round(y)][(int)round(x)]);
	// 	return (0);
	// }
	// 	if (data->map_flood[(int)round((y) - MOV_SPEED)][(int)round((x)
	// 		- MOV_SPEED)] == 1 || data->map_flood[(int)round((y - 1.5)
	// 		- MOV_SPEED)][(int)round((x - 1.5))] || data->map_flood[(int)round(y
	// 		- MOV_SPEED / 2)][(int)round(x - MOV_SPEED / 1.5)] == 1
	// 	|| data->map_flood[(int)round(y - MOV_SPEED * 1.5)][(int)round(x
	// 		- (MOV_SPEED * 2))] == 1)
	// {
	// 	printf("false 3 %f | %f\n", x, y);
	// 	printf("block %d\n", data->map_flood[(int)round(y)][(int)round(x)]);
	// 	return (0);
	// }
	printf("block %d\n", data->map_flood[(int)round(y)][(int)round(x)]);
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

// int	is_valid_move(double x, double y, t_parsing *data)
// {
// 	printf("%d | %d\n", data->map_width, data->map_height);
// 	if ((int)x < 0 || (int)y < 0 || (int)x >= data->map_width
// 		|| (int)y >= data->map_height)
// 	{
// 		printf("false 1 %f | %f\n", x, y);
// 		return (0);
// 	}
// 	if (data->map_flood[(int)round(y + MOV_SPEED)][(int)round(x
// + MOV_SPEED)] == 1
// 		|| data->map_flood[(int)round(y)][(int)round(x)] == 1
// || data->map_flood[(int)round(y
// 			+ MOV_SPEED / 2)][(int)round(x + MOV_SPEED / 2)] == 1
// || data->map_flood[(int)round(y
// 			+ MOV_SPEED * 2)][(int)round(x + (MOV_SPEED * 2))] == 1)
// 	{
// 		printf("false 2 %f | %f\n", x, y);
// 		return (0);
// 	}
// 	return (1);
// }

double	calculateAngle(double dir_y, double dir_x)
{
	return (atan2(dir_y, dir_x));
}

void	keys_loop(void *param)
{
	t_parsing	*data;
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
		// printf("y == %d | x == %d\n", y, x);
		// printf("%f | %f\n", cos(angle) * MOV_SPEED, sin(angle) * MOV_SPEED);
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
		rotate_left(data, ROT_SPEED);
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
		rotate_right(data, ROT_SPEED);
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
			return (EXIT_FAILURE);
		// if (!set_ray_struct(&data))
		// 	return (EXIT_FAILURE);
		// mlx_loop_hook(data.window, keys_loop, &data);
		// mlx_loop(data.window);
		// mlx_terminate(data.window);
		free_data(&data);
	}
	else
		return (write(STDERR_FILENO, "usage: ./cub3D *.cub\n", 21), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
