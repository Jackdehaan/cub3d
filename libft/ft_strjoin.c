/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/08 17:42:00 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/03/29 14:03:53 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newarray;
	int		i;
	int		j;

	newarray = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	if (newarray == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		newarray[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i] != '\0')
	{
		newarray[j] = s2[i];
		i++;
		j++;
	}
	newarray[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (newarray);
}

// int main()
// {
//     const char *s1 = "Hello  ";
//     const char *s2 = "byedfgdsgffg";

//     char *result = ft_strjoin(s1, s2);

//     printf("%s", result);
//     free(result);
// }