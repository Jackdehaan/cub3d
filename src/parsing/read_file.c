/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 13:53:36 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 14:47:10 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/get_next_line.h"

void	check_if_tex_color(t_parsing *data)
{
	
}

int	read_file(t_parsing *data)
{
	char *gnl_output;
	gnl_output = NULL;
	data->map = ft_strdup("");
	while (1)
	{
		gnl_output = get_next_line(data->file_fd);
		
		if (!gnl_output)
			break ;
		data->map = ft_strjoin_gnl(data->map, gnl_output);
		ft_free(&gnl_output);
	}
	printf("%s\n", data->map);
	return (1);
}