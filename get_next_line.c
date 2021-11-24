/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:24:31 by lcorinna          #+#    #+#             */
/*   Updated: 2021/11/24 20:01:32 by lcorinna         ###   ########.fr       */
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

void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	char	*e;

	e = b;
	i = 0;
	while (i < (int) len)
	{
		e[i] = c;
		i++;
	}
	return (e);
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

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (join);
}

char	*get_next_line(int fd)
{
	char			*new_str;
	static char		*reserv;
	char			*str;

	str = (char *) malloc(sizeof(char) * (5 + 1));//BUFFER_SIZE)
	new_str = (char *) malloc(sizeof(char) * 1);
	ft_memset(str, '\0', 5);//BUFFER_SIZE
	// if (reserv)//при втором заходе забирать остатки в новую строку
	// {
	// 	new_str = reserv;
	// }
	// while ((ft_strchr(str, 10)) == NULL)
	// {
	read(fd, str, 5);//нужно чтобы работало от 1 до 1000000 //BUFFER_SIZE
	//str[5] = '\0';
	new_str = ft_strjoin(new_str, str);
	//}
	//printf("%s\n\n", str);
	//new_str = ft_substr(str, 0, i); // когда-то вернуть NULL
	return (new_str);
}

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("text.txt", O_RDONLY);
	// "open" return "fd", this allow you to call the file
	gnl = get_next_line(fd);
	printf("%s\n", gnl);
	// while ((gnl = get_next_line(fd)) != NULL)
	// {
	// 	printf("%s\n", gnl);
	// }
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
