/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 12:11:10 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 13:31:33 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>

typedef struct t_parsing
{
	char	*filename;
	char	*map;
	char	*path_north_tex;
	char	*path_south_tex;
	char	*path_west_tex;
	char	*path_east_tex;
	char	*floor_color;
	char	*ceiling_color;
	char	*player_position;
}			t_parsing;

#endif