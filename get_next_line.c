/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:24:31 by lcorinna          #+#    #+#             */
/*   Updated: 2021/11/23 20:17:31 by lcorinna         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	char	str[42]; //BUFFER_SIZE
	char	*new_str;
	int		i;

	ft_memset(str, '\0', 42);
	i = 0;
	read(fd, str, 42); // нужно чтобы работало от 1 до 1000000000
	while (str[i] != '\n')
	{
		i++;
	}
	printf("%s\n\n", str);
	new_str = ft_substr(str, 0, i); // когда-то вернуть NULL
	return (new_str);
}

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("text.txt", O_RDONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR); 
	// "open" return "fd", this allow you to call the file
	while ((gnl = get_next_line(fd)) != NULL)
	{
		printf("%s\n", gnl);
	}
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
