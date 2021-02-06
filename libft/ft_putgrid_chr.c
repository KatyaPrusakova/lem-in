/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putgrid_eol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 18:44:37 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/24 02:02:01 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Writes y amount of strings stored as char **. '\nˇ will be added to the end
** of every string. If y == 0, strings will be printed until a null terminating
** pointer is encountered.
*/

void	ft_putgrid_chr(char **grid, int y)
{
	int i;

	i = 0;
	while (i < y || (y == 0 && grid[i]))
	{
		ft_putendl(grid[i]);
		i++;
	}
}
