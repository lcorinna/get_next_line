/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:24:31 by lcorinna          #+#    #+#             */
/*   Updated: 2021/11/26 20:31:52 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t	ft_strlen(const char *r)
{
	size_t	i;

	i = 0;
	while (r[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	int		i;
	int		count;

	i = 0;
	count = ft_strlen(s) - start;
	if (count > (int) len)
		count = (int) len;
	if (count <= 0)
		count = 0;
	newstr = (char *) malloc(sizeof(char) * (count + 1));
	if (newstr == NULL)
		return (newstr);
	while (s[start] != 0 && len-- != 0 && count != 0)
		newstr[i++] = s[start++];
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_substr_free(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	int		i;
	int		count;

	i = 0;
	count = ft_strlen(s) - start;
	if (count > (int) len)
		count = (int) len;
	if (count <= 0)
		count = 0;
	newstr = (char *) malloc(sizeof(char) * (count + 1));
	if (newstr == NULL)
		return (newstr);
	while (s[start] != 0 && len-- != 0 && count != 0)
		newstr[i++] = s[start++];
	newstr[i] = '\0';
	free((char *) s);
	s = NULL;
	return (newstr);
}

char	*ft_strchr(const char *s, int c)
{
	char	*a;
	char	i;

	i = (char) c;
	a = (char *) s;
	while (*a)
	{
		if (*a == i)
			return (a);
		a++;
	}
	if (*a == i)
		return (a);
	return (NULL);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		i;
	int		p;
	char	*join;

	p = 0;
	i = 0;
	join = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	while (s1[i])
		join[p++] = s1[i++];
	i = 0;
	while (s2[i])
		join[p++] = s2[i++];
	join[p] = '\0';
	// printf("%p-%s\n", s1, s1);
	// printf("%p-%s\n", s2, s2);
	free((char *) s1);
	s1 = NULL;
	free((char *) s2);
	s2 = NULL;
	return (join);
}

// char	*get_next_line(int fd)
// {
// 	int				j;
// 	int				i;
// 	char			*str;
// 	static char		*reserv;
// 	str = (char *) malloc(sizeof(char) * (5 + 1)); //BUFFER_SIZE
// 	i = read(fd, str, 5);
// 	//printf("%d\n", i);
// 	if (i == 0)
// 		return (NULL);
// 	if (reserv != NULL)
// 	{
// 		//read(fd, str, 5);
// 		reserv = (ft_strjoin(reserv, str));
// 	}
// 	if (reserv == NULL)
// 		reserv = ft_substr(str, 0, 5); //BUFFER_SIZE
// 	while ((ft_strchr(reserv, '\n')) == NULL)
// 	{
// 		i = read(fd, str, 5); //BUFFER_SIZE
// 		if (i < 1)
// 			return (reserv);
// 		reserv = ft_strjoin(reserv, str);
// 	}
// 	i = 0;
// 	j = 0;
// 	while (reserv[i] != '\n')
// 	{
// 		i++;
// 		if (reserv[i] == '\0')
// 			return (reserv);
// 	}
// 	while (reserv[i + j] != '\0')
// 		j++;
// 	str = ft_substr(reserv, 0, i);
// 	reserv = ft_substr(reserv, (i + 1), j);
// 	printf("reserv: %s", reserv);
// 	return (str);
// }

char	*get_next_line(int fd)
{
	int				j;
	int				i;
	char			*str;
	static char		*res;

	if (res != NULL)
	{
		if ((ft_strchr(res, '\n') != NULL))
		{
			i = 0;
			j = 0;
			while (res[i++] != '\n')
			{
				if (res[i] == '\0')
					return (res);
			}
			while (res[i + j] != '\0')
				j++;
			str = ft_substr(res, 0, i);
			res = ft_substr(res, i, j);
			return (str);
		}
		while ((ft_strchr(res, '\n')) == NULL)
		{
			str = (char *) malloc(sizeof(char) * (5 + 1));
			i = read(fd, str, 5);
			str[i] = '\0';
			if (i <= 0 || str[i - 1] == '\0')
			{
				str = ft_strjoin_free(res, str);
				res = NULL;
				return (str);
			}
			res = ft_strjoin_free(res, str);
		}
		i = 0;
		j = 0;
		while (res[i++] != '\n')
		{
			if (res[i] == '\0')
				return (res);
		}
		while (res[i + j] != '\0')
			j++;
		str = ft_substr(res, 0, i);
		res = ft_substr(res, i, j);
		return (str);
	}
	else if (res == NULL)
	{
		res = (char *) malloc(sizeof(char) * (5 + 1));
		i = read(fd, res, 5);
		res[i] = '\0';
		if (i <= 0)
		{
			free (res);
			res = NULL;
			return (NULL);
		}
		res = ft_substr_free(res, 0, i);
		if (i < 5)
			return (res);
		while ((ft_strchr(res, '\n')) == NULL)
		{
			str = (char *) malloc(sizeof(char) * (5 + 1));
			i = read(fd, str, 5);
			if (i <= 0 || str[i - 1] == '\0')
			{
				free(str);
				return (res);
			}
			res = ft_strjoin_free(res, str);
		}
	}
	i = 0;
	j = 0;
	while (res[i++] != '\n')
	{
		if (res[i] == '\0')
		{
			str = ft_substr(res, 0, ft_strlen(res));
			free(res);
			res = NULL;
			return (res);
		}
	}
	while (res[i + j] != '\0')
		j++;
	str = ft_substr(res, 0, i);
	res = ft_substr(res, i, j);
	return (str);
}

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("text.txt", O_RDONLY);
	while ((gnl = get_next_line(fd)) != NULL)
	{
		printf("%s", gnl);
	}
	// gnl = get_next_line(fd);
	// printf("%s\n", gnl);
	// free(gnl);
	// gnl = get_next_line(fd);
	// printf("%s\n", gnl);
	// free(gnl);
	// gnl = get_next_line(fd);
	// printf("%s\n", gnl);
	// free(gnl);
	// gnl = get_next_line(fd);
	printf("%s\n", gnl);
	//free(gnl);
	close (fd);
	return (0);
}

/* Делает отладочные дампы во время компиляции в моменты времени определяемые буквами. 
Они используются для отладки компилятора. Имена файлов для большинства дампов 
получаются из имени исходного файла добавлением слова 
(например, 'foo.c.rtl' или 'foo.c.jump'). Ниже указаны возможные буквы и их значения: */
//'D' Дамп всех макро определений в конце препроцессирования, в добавление к нормалному выводу.

// void	Func(void)
// {
// 	static	int	x = 0;
// 	// |x| is initialized only once across five calls of |Func| and the variable
// 	// will get incremented five times after these calls. The final value of |x|
// 	// will be 5.
// 	x++;
// 	printf("%d\n", x); // outputs the value of |x|
// }

// int	main(void)
// {
// 	Func(); // prints 1
// 	Func(); // prints 2
// 	Func(); // prints 3
// 	Func(); // prints 4  Func();  // prints 5
// 	return (0);
// }

// int	main(void)
// {
// 	int		fd;
// 	int		er;
// 	int		op;
// 	char	c;
// 	char	str[BUFFER_SIZE];

// 	c = 'a';
// 	// fd = open("text.txt", 12);
// 	er = open("42", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
// 	fd = open("text.txt", O_RDONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
// 	if (er == -1)
// 	{
// 		printf("%s\n", "im pooped");
// 		return (0);
// 	}
// 	printf("%d\n", fd);
// //	write(fd, &c, 1);
// 	op = read(fd, str, 3);
// 	printf("%s\n", str);
// 	op = read(fd, str, 3);
// 	printf("%s\n", str);
// 	printf("this %d\n", op);
// 	//close(fd);
// 	close(er);
// 	//printf("%d\n", er);
// 	write(er, &c, 1);
// 	return (0);
// }
