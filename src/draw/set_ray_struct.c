/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:06 by jade-haa          #+#    #+#             */
/*   Updated: 2024/04/12 17:58:23 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	set_ray_struct(t_parsing *data)
{
	double angle;
	t_raycasting *ray;

	ray = (t_raycasting *)malloc(sizeof(t_raycasting));
	data->raycasting = ray;
	ray->dir_x = 1;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0.66;
	angle = atan2(1, 0) - atan2(ray->dir_y, ray->dir_x);
	if (data->player_direction == 78)
	{
        printf("start noord\n");
		rotate_left(data, angle);
	}
	else if (data->player_direction == 87)
	{
		rotate_left(data, angle);
		rotate_left(data, angle);
        printf("start west\n");
        printf("rotate arsafsad%f | %f | %F | %f\n\n\n", ray->dir_x, ray->dir_y,
		ray->plane_x, ray->plane_y);
	}
	else if (data->player_direction == 83)
	{
        printf("start zuid\n");
		rotate_right(data, angle);
	} // printf("rotate arsafsad%f | %f | %F | %f\n", ray->dir_x, ray->dir_y,
	// 	ray->plane_x, ray->plane_y);
	return (1);
}