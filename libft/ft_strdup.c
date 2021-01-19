/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 14:30:45 by ksuomala          #+#    #+#             */
/*   Updated: 2020/07/14 21:37:31 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		l;
	int		i;
	char	*dup;

	i = 0;
	l = ft_strlen(str);
	dup = (char *)malloc(sizeof(char) * l + 1);
	if (!dup)
		return (NULL);
	dup[l] = '\0';
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}
