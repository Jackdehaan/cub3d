/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:11:10 by rfinneru          #+#    #+#             */
/*   Updated: 2024/03/31 16:17:38 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

typedef enum TEX_COLOR
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
}			TEX_COLOR;

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
	int		map_width;
	int		map_height;
	int		**map_flood;
}			t_parsing;

/*
PARSING
*/
int			parsing(char *file, t_parsing *data);
int			filename_check(t_parsing *data);
int			open_file(t_parsing *data);
int			read_file(t_parsing *data);
int			check_map(t_parsing *data);
int			init_map(t_parsing *data);

/*
UTILS
*/
void		ft_free(char **buffer);
char		*ft_strndup(char *s, size_t n);
void		print_tex_color(t_parsing *data);

#endif