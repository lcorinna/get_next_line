/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:26:30 by lcorinna          #+#    #+#             */
/*   Updated: 2021/12/01 18:20:14 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef  BUFFER_SIZE
#  define  BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

size_t	ft_strlen(char *r);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_trim_for_str(char *res);
char	*ft_trim_for_res(char *res);
char	*ft_read(int fd, char *res, int *chit, int i);
char	*get_next_line(int fd);
char	*ft_res_res(char *res, int i);

#endif
