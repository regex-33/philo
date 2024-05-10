/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:30:21 by yachtata          #+#    #+#             */
/*   Updated: 2024/05/10 15:30:23 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

static const char	*skipwhitespace(const char *c, int *sign)
{
	while (*c == ' ' || *c == '\t' || *c == '\n' || *c == '\r' || *c == '\v'
		|| *c == '\f')
		c++;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			*sign = -1;
		c++;
	}
	return (c);
}

long long	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	n;
	int					sign;

	i = 0;
	n = 0;
	sign = 1;
	if (str == NULL || (str != NULL && *str == '\0'))
		return (0);
	str = skipwhitespace(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i++] - '0');
		if (n > LLONG_MAX && sign == 1)
			return (-1);
		if (n > LLONG_MAX && sign == -1)
			return (0);
	}
	return (n * sign);
}

void	print_status(long timestamp, int id, char *msg)
{
	printf("%ld %d %s\n", timestamp, id, msg);
}
