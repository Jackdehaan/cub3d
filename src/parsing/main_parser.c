/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:45:51 by rfinneru          #+#    #+#             */
/*   Updated: 2024/03/31 16:18:46 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parsing(char *file, t_parsing *data)
{
	data->filename = file;
	if (!filename_check(data))
		return (0);
	if (!open_file(data))
		return (0);
	if (!read_file(data))
		return (0);
	if (!init_map(data))
		return(0);
	if (!check_map(data))
		return(0);
	return (1);
}