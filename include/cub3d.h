/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:11:10 by rfinneru          #+#    #+#             */
/*   Updated: 2024/06/05 16:23:33 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# define WIDTH 1420
# define HEIGHT 1420
# define BACKGROUND_COLOR 0x22222200
# define MOV_SPEED 0.1
# define ROT_SPEED 0.1
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct t_ray
{
	double				dir_y;
	double				dir_x;
	double				plane_y;
	double				plane_x;
}						t_ray;

typedef enum TEX_COLOR
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
}						TEX_COLOR;

typedef struct t_dda
{
	int					dx;
	int					dy;
	int					steps;
	float				Yinc;
	float				X;
	float				Y;
	int					i;
	int					extra;
	int					y_begin;
	int					x_begin;
	int					index;
}						t_dda;

typedef struct t_parsing
{
	char				*filename;
	int					file_fd;
	char				*map;
	char				*path_north_tex;
	char				*path_south_tex;
	char				*path_west_tex;
	char				*path_east_tex;
	mlx_texture_t		*fd_north_tex;
	mlx_texture_t		*fd_south_tex;
	mlx_texture_t		*fd_west_tex;
	mlx_texture_t		*fd_east_tex;
	char				*floor_color;
	unsigned int		hex_floor;
	char				*ceiling_color;
	unsigned int		hex_ceiling;
	double				player_position[2];
	int					player_direction;
	int					map_width;
	int					map_height;
	int					**map_flood;
	bool				found_start;
	bool				found_end;
	mlx_t				*window;
	mlx_image_t			*image;
	t_ray				*raycasting;
}						t_parsing;

typedef struct t_raycasting
{
	double				rayDirX;
	double				rayDirY;
	double				planeX;
	double				planeY;
	double				cameraX;
	int					x;
	int					mapX;
	int					mapY;
	double				posY;
	double				sideDistX;
	double				sideDistY;
	double				deltaDistX;
	double				deltaDistY;
	double				posX;
	double				dirX;
	double				dirY;
	double				perpWallDist;
	int					stepX;
	int					stepY;
	int					hit;
	int					side;
	int					lineHeight;
	int					drawStart;
	int					drawEnd;
	int					x0;
	int					y0;
	int					x1;
	int					texNum;
	u_int32_t			colors[5000];
	int					y1;
	int					pitch;
	int					i;
	int					texX;
	double				step;
	double				texPos;
	int					texY;
	struct mlx_texture	*tex;
	int					texelIndex;
	uint8_t				red;
	uint8_t				green;
	uint8_t				blue;
	uint8_t				alpha;
}						t_raycasting;
/*
PARSING
*/
int						parsing(char *file, t_parsing *data);
int						filename_check(t_parsing *data);
int						open_file(t_parsing *data);
int						read_file(t_parsing *data);
int						check_map(t_parsing *data);
int						init_map(t_parsing *data);
int						set_ray_struct(t_parsing *data);
int						valid_map(t_parsing *data);
int						set_value(char value, t_parsing *data, int y, int x);

void					rotate_left(t_parsing *data, double rot_speed);
void					rotate_right(t_parsing *data, double rot_speed);

int						find_rgb_part(char *str, char **part, int *i);
unsigned int			rgb_to_hex(int r, int g, int b);
void					free_rgb_parts(char **r, char **g, char **b);
int						set_hex_color(char **str, unsigned int *hex, int ret);

int						malloc_color(char **color, char *str, int i);
int						color_valid_check(char *str, int ret);
int						color_missing_check(char *str, int ret);

int						remove_whitespace(char **str, int ret);
void					empty_check(t_parsing *data, int *ret);
int						tex_color_filled(t_parsing *data);
int						map_char(char c);
char					*trim_spaces_from_end(char *line, t_parsing *data);

int						check_if_tex_color(t_parsing *data, char *str);
int						check_if_tex_color_return(char *str);
int						xpm_file_check(char *str, mlx_texture_t **tex);
int						check_tex_path(t_parsing *data, int ret);

int						remove_nl(char *str);
char					*skip_spaces(char *str);
int						set_data(t_parsing *data, TEX_COLOR found, char *str);

/*
UTILS
*/
void					ft_free(char **buffer);
char					*ft_strndup(char *s, size_t n);
void					print_tex_color(t_parsing *data);
void					free_data(t_parsing *data);
void					render_cube(t_parsing *data);

// dda
void					dda(t_parsing *data, t_raycasting *values);
struct mlx_texture		*choose_texture(t_parsing *data, double y, double x,
							int side);
void					put_pixels(t_raycasting *values);
void					init_values_loop(t_raycasting *values);
void					get_direction(t_raycasting *values);
void					get_wall(t_raycasting *values, t_parsing *data);

#endif