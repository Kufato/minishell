/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:05:14 by axcallet          #+#    #+#             */
/*   Updated: 2023/05/31 14:40:15 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static long long	ft_atoll_end(char *cmd, int i, int n, long long p)
{
	while (cmd[i] >= '0' && cmd[i] <= '9')
	{
		if (((p * n) > LONG_MAX / 10)
			|| ((p * n) == LONG_MAX / 10 && (cmd[i] - '0') > LONG_MAX % 10))
			return (-1);
		if (((p * n) < LONG_MIN / 10)
			|| ((p * n) == LONG_MIN / 10 && (cmd[i] - '0') > -(LONG_MIN % 10)))
			return (0);
		p = p * 10 + (cmd[i] - 48);
		i++;
	}
	return (p);
}

long long	ft_atoll(char *num)
{
	int			i;
	int			n;
	long long	p;

	i = 0;
	p = 0;
	n = 1;
	while ((num[i] >= 9 && num[i] <= 13) || num[i] == 32)
		i++;
	while (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			n = n * -1;
		i++;
	}
	p = ft_atoll_end(num, i, n, p);
	p = p * n;
	return (p);
}
