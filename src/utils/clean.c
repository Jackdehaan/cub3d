/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 14:01:04 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 14:02:52 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free(char **buffer)
{
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
}
