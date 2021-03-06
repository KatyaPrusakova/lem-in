/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:28:51 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/02 15:28:59 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_paths(t_path **path)
{
	t_path *tmp;
	int	i = -1;
	if (path[0])
	{
//		ft_dprintf(fd, "Shortest path len %d :\n", path[0]->len);
		while (path[++i])
		{
			tmp = path[i];
			ft_dprintf(fd, "path n %d: ", i);
			while (tmp)
			{
				ft_dprintf(fd, "%d |", tmp->i);
				tmp = tmp->next;
			}
			ft_dprintf(fd, "\n");
		}
	}
	else
		ft_dprintf(fd, "START is connected to END\n");
}

void	print_matrix(int **matrix, int size)
{
	int i;
	int j;

	i = -1;
	j = -1;

	while (++j < size)
	{
		while (++i < size)
			ft_dprintf(fd, "[%d] ", matrix[j][i]);
		i = -1;
		ft_dprintf(fd, "\n");
	}
}
