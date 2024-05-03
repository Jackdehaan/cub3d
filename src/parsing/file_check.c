/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 13:46:25 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/05/03 13:33:26 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	filename_check(t_parsing *data)
{
	int		end;
	char	*dotcube;
	int		x;

	x = 0;
	end = ft_strlen(data->filename) - 1;
	dotcube = ft_strdup("buc.");
	if (!dotcube)
		return (0);
	while (data->filename[end] == dotcube[x])
	{
		x++;
		end--;
	}
	ft_free(&dotcube);
	if (x != 4)
	{
		write(STDERR_FILENO, "Only use .cub files\n", 20);
		return (0);
	}
	else
		return (1);
}

int	open_file(t_parsing *data)
{
	data->file_fd = open(data->filename, O_RDONLY);
	if (data->file_fd == -1)
	{
		perror("Failed to open the file");
		return (0);
	}
	return (1);
}
