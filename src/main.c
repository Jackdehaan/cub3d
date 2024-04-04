/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:10:48 by rfinneru          #+#    #+#             */
/*   Updated: 2024/04/04 14:05:57 by jade-haa         ###   ########.fr       */
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

	data = param;
	if (mlx_is_key_down(data->window, MLX_KEY_ESCAPE))
		mlx_close_window(data->window);
	
	printf("%d | %d | %d | %d\n", data->player_position[0], data->player_position[1], data->map_height, data->map_width);

	if (mlx_is_key_down(data->window, MLX_KEY_UP))
	{
		if (((data->player_position[0]) + 2) < data->map_height)
			data->player_position[0] += 1;
	}
	if (mlx_is_key_down(data->window, MLX_KEY_DOWN))
	{
		if (((data->player_position[0]) - 2) > 0)
			data->player_position[0] -= 1;
	}
	if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
	{
		if (((data->player_position[1]) - 2) > 0)
			data->player_position[1] -= 1;
	}
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
	{
		if (((data->player_position[1]) + 2) < data->map_width)
			data->player_position[1] += 1;
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
