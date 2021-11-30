/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:09:04 by lcorinna          #+#    #+#             */
/*   Updated: 2021/11/30 19:44:41 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t	ft_strlen(char *r)
{
	size_t	i;

	i = 0;
	if (r == NULL)
		return (i);
	while (r[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
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

char	*ft_substr(char *s, unsigned int start, size_t len)
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
	// free(s);
	// s = NULL;
	return (newstr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		p;
	char	*join;

	p = 0;
	i = 0;
	join = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		while (s1[i])
			join[p++] = s1[i++];
		free(s1);
		s1 = NULL;
	}
	i = 0;
	if (s2 != NULL)
	{
		while (s2[i])
			join[p++] = s2[i++];
	}
	join[p] = '\0';
	// free(s2);
	// s2 = NULL;
	return (join);
}

char	*ft_trim_for_str(char *res)
{
	char	*str;
	int		i;
	
	i = 0;
	if (res == NULL)
		return (NULL);
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	// if (res[i] == '\n')
	// {
	// 	str = ft_substr(res, 0, 2);
	// 	return (str);
	// }
	// if (res[i] == '\0')
	// {
	// 	str = ft_substr(res, 0, i + 1);
	// 	return (NULL);
	// }
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

char	*ft_read(int fd, char *res)
{
	char	*str;
	int		i;
	int		chit;
	
	chit = 1;
	if (res == NULL)
	{
		res = (char *) malloc(sizeof(char) * chit);
		res = ft_memset(res, '\0', chit++);
	}
	while((ft_strchr(res, '\n')) == NULL)
	{
		if (chit != 1)
		{
			free(res);
			res = NULL;
			chit = 1;
		}
		str = (char *) malloc(sizeof(char) *  BUFFER_SIZE + 1);
		i = read(fd, str,  BUFFER_SIZE);
		if (i < 0)
		{
			free(str);
			str = NULL;
			return (NULL);			
		}
		str[i] = '\0';
		if (i == 0)
		{
			free(str);
			str = NULL;
			return (res);
		}
		if (i <  BUFFER_SIZE)
		{
			res = ft_strjoin(res, str);
			free(str);
			str = NULL;
			return (res);
		}
		res = ft_strjoin(res, str);
		free(str);
		str = NULL;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*str;

	if (fd < 0)
		return (NULL);
	res = ft_read(fd, res);
	str = ft_trim_for_str(res);
	res = ft_trim_for_res(res);
	// if (res == NULL)
	// {
	// 	free(res);
	// 	res = NULL;
	// 	return (NULL);
	// }
	return (str);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*gnl;

// 	fd = open("text.txt", O_RDONLY);
// 	while ((gnl = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", gnl);
// 		free(gnl);
// 		gnl = NULL;
// 	}
// 	// gnl = get_next_line(fd);
// 	//printf("%s\n", gnl);
// 	// gnl = get_next_line(fd);
// 	// printf("%s\n", gnl);
// 	// gnl = get_next_line(fd);
// 	// printf("%s\n", gnl);
// 	close (fd);
// 	return (0);
// }

// int	soldat(int i)
// {
// 	static int	s;

// 	s = 1;
// 	if (i > 100)
// 		printf("polutchilos`!\n");
// 	else
// 	{
// 		printf("soldat %d, ih sila = %d, etogo malo chtobi vitjanut` repku.\n" s, i);
		//printf("Zovu soldata na pomosch\n\n");
// 		soldat(i + 15);
// 		s += 1;
// 	}
// 	return (s);
// }

// int	main(void)
// {
// 	int	repka;

// 	repka = 15;
// 	printf("%d\n", soldat(repka));
// 	return (0);
// }

// int	ft_factorial(int n)
// {
// 	if (0 == n)
// 		return (1);
// 	return (ft_factorial(n - 1) * n);
// }

// int	ft_gcd(int a, int b)
// {
// 	if (0 == b)
// 		return (a);
// 	return (ft_gcd(b, a % b));
// }

// double	ft_fast_power(double a, int n)
// {
// 	 if (0 == n)
// 	 	return (1);
// 	if (n % 2 == 1)
// 		return (a * ft_fast_power(a, n - 1));
// 	else
// 		return (ft_fast_power(a * a, n / 2));
// }

// int	ft_fib(int n)
// {
// 	if (n <= 1)
// 		return (n);
// 	return (ft_fib(n - 1) + ft_fib(n - 2));
// }

// int	main(int argc, char *argv[])
// {
// 	int	n;
// 	int	m;

// 	scanf("%d%d", &n, &m);
// 	printf("factorial(%d) = %d\n", n , ft_factorial(n));
// 	printf("ft_gcd(%d, %d) = %d\n", n, m, ft_gcd(n, m));
// 	printf("ft_fast_power(%d, %d) = %lf\n", n, m, ft_fast_power(n, m));
// 	printf("ft_fib(%d) = %d\n", n, ft_fib(n));
// 	return (0);
// }

// void ft_hanoi(int n, int i, int k)
// {
// 	int	tmp;

// 	if (1 == n)
// 		printf("Move disk 1 from pin %d to %d.\n", i, k);
// 	else
// 	{	
// 		tmp = 6 - i - k;
// 		ft_hanoi((n - 1), i, tmp);
// 		printf("Move disk %d from pin %d to %d.\n", n, i, k);
// 		ft_hanoi((n-1), tmp, k);
// 	} 
// }

// int	main(int argc, char *argv[])
// {
// 	ft_hanoi(3, 1, 2); //n - number of pancakes, i - from which tower, k - which tower
// 	return (0); 
// }
 