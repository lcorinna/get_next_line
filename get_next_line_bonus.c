/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:09:04 by lcorinna          #+#    #+#             */
/*   Updated: 2021/12/01 19:25:05 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_trim_for_str(char *res)
{
	char	*str;
	int		i;

	i = 0;
	if (res == NULL)
		return (NULL);
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	str = ft_substr(res, 0, i + 1);
	return (str);
}

char	*ft_trim_for_res(char *res)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (res == NULL)
		return (NULL);
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	if (res[i] == '\0' || res[i + 1] == '\0')
	{
		free(res);
		res = NULL;
		return (NULL);
	}
	while (res[i + j] != '\0')
		j++;
	str = ft_substr(res, (i + 1), j);
	free(res);
	res = NULL;
	return (str);
}

char	*ft_res_res(char *res, int i)
{
	if (i < 0)
	{
		//res = NULL;
		return (NULL);
	}
	if (i == 0)
		return (res);
	return (res);
}

char	*ft_read(int fd, char *res, int *chit, int i)
{
	char	*str;

	while ((ft_strchr(res, '\n')) == NULL)
	{
		if (*chit != 1)
		{
			free(res);
			res = NULL;
			*chit = 1;
		}
		str = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
		i = read(fd, str, BUFFER_SIZE);
		if (i < 0 || i == 0)
		{
			free(str);
			res = ft_res_res(res, i);
			return (res);
		}
		str[i] = '\0';
		res = ft_strjoin(res, str);
		free(str);
		if (i < BUFFER_SIZE)
			return (res);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res[2147483647];
	char		*str;
	int			chit;
	int			i;

	i = 0;
	chit = 1;
	if (fd < 0)
		return (NULL);
	if (res[fd] == NULL)
	{
		res[fd] = (char *) malloc(sizeof(char) * chit);
		res[fd] = ft_memset(res, '\0', chit++);
	}
	res[fd] = ft_read(fd, res[fd], &chit, i);
	str = ft_trim_for_str(res[fd]);
	res[fd] = ft_trim_for_res(res[fd]);
	return (str);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*gnl;

// 	fd = open("text.txt", O_RDONLY);
// 	gnl = get_next_line(fd);
// 	printf("%s", gnl);
// 	fd = open("artem.txt", O_RDONLY);
// 	gnl = get_next_line(fd);
// 	printf("%s", gnl);
// 	fd = open("text.txt", O_RDONLY);
// 	gnl = get_next_line(fd);
// 	printf("%s", gnl);
// 	close (fd);
// 	return (0);
// }
