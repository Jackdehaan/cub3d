/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 10:50:37 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/04/15 13:38:42 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

// get_next_line
char	*get_next_line(int fd);

// utils
int		ft_strlen_gnl(char *str);
char	*ft_strncpy_gnl(char *dest, char *src, unsigned int n);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(const char *s, int c);
void	*ft_free_gnl(char **line, char **buffer, int arg);
char	*ft_strdup_gnl(const char *s);

#endif