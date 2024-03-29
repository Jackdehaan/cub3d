/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 12:11:10 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 14:04:34 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

typedef struct t_parsing
{
	char	*filename;
	int		file_fd;
	char	*map;
	char	*path_north_tex;
	char	*path_south_tex;
	char	*path_west_tex;
	char	*path_east_tex;
	char	*floor_color;
	char	*ceiling_color;
	char	*player_position;
}			t_parsing;

/*
PARSING
*/
int			parsing(char *file, t_parsing *data);
int			filename_check(t_parsing *data);
int			open_file(t_parsing *data);
int			set_textures_and_colors(t_parsing *data);

/*
UTILS
*/
void	ft_free(char **buffer);


#endif