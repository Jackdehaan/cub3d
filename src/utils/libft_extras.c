/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_extras.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/29 16:56:49 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/29 16:57:14 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_strndup(char *s, size_t n)
{
	size_t	i;
	char	*ptr;
	char	*temp;

	i = 0;
	while (s[i] && i < n)
		i++;
	temp = (char *)malloc((i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ptr = temp;
	i = 0;
	while (s[i] && i < n)
	{
		*ptr = s[i];
		ptr++;
		i++;
	}
	*ptr = '\0';
	return (temp);
}
