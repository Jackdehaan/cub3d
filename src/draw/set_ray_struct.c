/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:06 by jade-haa          #+#    #+#             */
/*   Updated: 2024/06/05 15:34:17 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	set_ray_struct(t_parsing *data)
{
	double	angle;
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_raycasting));
	if (!ray)
		return (0);
	data->raycasting = ray;
	ray->dir_x = 1;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0.66;
	angle = atan2(1, 0) - atan2(ray->dir_y, ray->dir_x);
	if (data->player_direction == 78)
		rotate_left(data, angle);
	else if (data->player_direction == 87)
	{
		rotate_left(data, angle);
		rotate_left(data, angle);
	}
	else if (data->player_direction == 83)
		rotate_right(data, angle);
	return (1);
}
