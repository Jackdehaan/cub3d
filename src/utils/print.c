/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:58:32 by rfinneru          #+#    #+#             */
/*   Updated: 2024/06/04 16:11:32 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_tex_color(t_parsing *data)
{
	printf("%s\n", data->path_north_tex);
	printf("%s\n", data->path_south_tex);
	printf("%s\n", data->path_west_tex);
	printf("%s\n", data->path_east_tex);
	printf("%x\n", data->hex_floor);
	printf("%x\n", data->hex_ceiling);
}
