/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:10:49 by rfinneru          #+#    #+#             */
/*   Updated: 2024/06/06 11:30:45 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	keys_s_w(t_parsing *data, double angle)
{
	double	new_y;
	double	new_x;

	if (mlx_is_key_down(data->window, MLX_KEY_S))
	{
		new_x = data->player_position[1] - cos(angle) * MOV_SPEED;
		new_y = data->player_position[0] - sin(angle) * MOV_SPEED;
		if (is_valid_move(new_x, new_y, data))
		{
			data->player_position[0] = new_y;
			data->player_position[1] = new_x;
		}
	}
	if (mlx_is_key_down(data->window, MLX_KEY_W))
	{
		new_x = data->player_position[1] + cos(angle) * MOV_SPEED;
		new_y = data->player_position[0] + sin(angle) * MOV_SPEED;
		if (is_valid_move(new_x, new_y, data))
		{
			data->player_position[1] = new_x;
			data->player_position[0] = new_y;
		}
	}
}

void	keys_d_a(t_parsing *data, double angle)
{
	double	new_y;
	double	new_x;

	if (mlx_is_key_down(data->window, MLX_KEY_D))
	{
		new_x = data->player_position[1] - cos(angle - M_PI / 2) * MOV_SPEED;
		new_y = data->player_position[0] - sin(angle - M_PI / 2) * MOV_SPEED;
		if (is_valid_move(new_x, new_y, data))
		{
			data->player_position[1] = new_x;
			data->player_position[0] = new_y;
		}
	}
	if (mlx_is_key_down(data->window, MLX_KEY_A))
	{
		new_x = data->player_position[1] + cos(angle - M_PI / 2) * MOV_SPEED;
		new_y = data->player_position[0] + sin(angle - M_PI / 2) * MOV_SPEED;
		if (is_valid_move(new_x, new_y, data))
		{
			data->player_position[1] = new_x;
			data->player_position[0] = new_y;
		}
	}
}

void	keys_loop(void *param)
{
	t_parsing	*data;
	int			**map;
	int			y;
	int			x;
	double		angle;

	data = param;
	map = data->map_flood;
	y = data->player_position[0];
	x = data->player_position[1];
	angle = atan2(data->raycasting->dir_y, data->raycasting->dir_x);
	if (mlx_is_key_down(data->window, MLX_KEY_ESCAPE))
		mlx_close_window(data->window);
	keys_d_a(data, angle);
	keys_s_w(data, angle);
	if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
		rotate_left(data, ROT_SPEED);
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
		rotate_right(data, ROT_SPEED);
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
		if (!set_ray_struct(&data))
			return (EXIT_FAILURE);
		mlx_loop_hook(data.window, keys_loop, &data);
		mlx_loop(data.window);
		mlx_terminate(data.window);
		free_data(&data);
	}
	else
		return (write(STDERR_FILENO, "usage: ./cub3D *.cub\n", 21),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
