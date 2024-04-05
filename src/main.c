/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:10:48 by rfinneru          #+#    #+#             */
/*   Updated: 2024/04/05 15:10:49 by jade-haa         ###   ########.fr       */
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

void	keys_loop(void *param)
{
	t_parsing	*data;
	double		oldDirX;
	double		oldPlaneX;
	double		rotSpeed;
	int		**map;
	int			y;
	int			x;

	// int			newPosX;
	// int			newPosY;
	data = param;
	map = data->map_flood;
	y = data->player_position[0];
	x = data->player_position[1];
	rotSpeed = 0.3;
	if (mlx_is_key_down(data->window, MLX_KEY_ESCAPE))
		mlx_close_window(data->window);
	// if (mlx_is_key_down(data->window, MLX_KEY_UP))
	// {
	// 	newPosX = (int)data->player_position[1] + data->raycasting->dir_x * 1;
	// 	if (!data->map_flood[newPosX][data->player_position[0]])
	// 	{
	// 		data->player_position[1] += data->raycasting->dir_x * 1;
	// 	}
	// 	newPosY = data->player_position[0] + data->raycasting->dir_x * 1;
	// 	if (!data->map_flood[newPosY][data->player_position[1]])
	// 	{
	// 		data->player_position[0] += data->raycasting->dir_x * 1;
	// 	}
	// }
	if (mlx_is_key_down(data->window, MLX_KEY_S))
	{
		if (((data->player_position[0]) + 2) < data->map_height && map[y + 1][x] == 0)
			data->player_position[0] += 1;
	}
	if (mlx_is_key_down(data->window, MLX_KEY_W))
	{
		if (((data->player_position[0]) - 3) > 0 && map[y - 1][x] == 0)
			data->player_position[0] -= 1;
	}
	if (mlx_is_key_down(data->window, MLX_KEY_A))
	{
		if (((data->player_position[1]) - 3) > 0 && map[y][x - 1] == 0)
			data->player_position[1] -= 1;
	}
	if (mlx_is_key_down(data->window, MLX_KEY_D))
	{
		if ((((data->player_position[1]) + 2) < data->map_width) && map[y][x + 1] == 0)
			data->player_position[1] += 1;
	}
	// printf("%d | %d | %d | %d\n", data->player_position[0],
	// 	data->player_position[1], data->map_height, data->map_width);
	if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
	{
		oldDirX = data->raycasting->dir_x;
		data->raycasting->dir_x = data->raycasting->dir_x * cos(-rotSpeed)
			- data->raycasting->dir_y * sin(-rotSpeed);
		data->raycasting->dir_y = oldDirX * sin(-rotSpeed)
			+ data->raycasting->dir_y * cos(-rotSpeed);
		oldPlaneX = data->raycasting->plane_x;
		data->raycasting->plane_x = data->raycasting->plane_x * cos(-rotSpeed)
			- data->raycasting->plane_y * sin(-rotSpeed);
		data->raycasting->plane_y = oldPlaneX * sin(-rotSpeed)
			+ data->raycasting->plane_y * cos(-rotSpeed);
	}
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
	{
		oldDirX = data->raycasting->dir_x;
		data->raycasting->dir_x = data->raycasting->dir_x * cos(rotSpeed)
			- data->raycasting->dir_y * sin(rotSpeed);
		data->raycasting->dir_y = oldDirX * sin(rotSpeed)
			+ data->raycasting->dir_y * cos(rotSpeed);
		oldPlaneX = data->raycasting->plane_x;
		data->raycasting->plane_x = data->raycasting->plane_x * cos(rotSpeed)
			- data->raycasting->plane_y * sin(rotSpeed);
		data->raycasting->plane_y = oldPlaneX * sin(rotSpeed)
			+ data->raycasting->plane_y * cos(rotSpeed);
	}
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

