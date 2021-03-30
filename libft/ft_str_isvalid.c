/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isvalid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:50:48 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/18 19:09:00 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks that every character of *str is within *valid_characters. If an
** invalid character is found, return NULL.
*/

int		ft_str_isvalid(char *str, char *valid_characters)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(valid_characters, str[i]))
			return (0);
		i++;
	}
	return (1);
}
