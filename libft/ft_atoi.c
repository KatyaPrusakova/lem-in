/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 13:08:23 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/19 15:08:35 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int		res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str && (*str == '\r' || *str == '\n' || *str == '\t' ||
					*str == '\f' || *str == '\v' || *str == ' '))
		str++;
	if (str[0] == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		if (res > 214748364)
			return (-1);
		str++;
	}
	return (res * sign);
}
