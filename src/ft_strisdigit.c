/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/23 20:13:22 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				ft_strisdigit(char *s)
{
	int i;
	int l;

	i = 0;
	l = ft_strlen(s);
	if (!s || l == 0)
		return (0);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return(l == i ? 1 : 0);
}
