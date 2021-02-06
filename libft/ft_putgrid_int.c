/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putgrid_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:55:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/24 02:15:54 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putgrid_int(int **grid, int y, int x, int min_width)
{
	int i_x;
	int i_y;

	i_y = 0;
	i_x = 0;
	while (i_y < y)
	{
		while (i_x < x)
		{
			ft_printf("%*d", min_width, grid[i_y][i_x]);
			i_x++;
		}
		i_x = 0;
		i_y++;
		ft_n(1);
	}
	ft_n(1);
}
