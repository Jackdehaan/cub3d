/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:06 by jade-haa          #+#    #+#             */
/*   Updated: 2024/04/02 15:39:13 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int set_ray_struct(t_parsing *data)
{
    t_raycasting *ray;

    ray = (t_raycasting *)malloc(sizeof(t_raycasting));
    data->raycasting = ray;
    ray->dir_x = 0;
    ray->dir_y = 0;
    return(1);
}