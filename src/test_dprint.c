/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:28:51 by ksuomala          #+#    #+#             */
/*   Updated: 2021/06/22 23:43:34 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_paths(t_path **path, t_room **adlist)
{
	t_path	*tmp;
	int		i;

	i = -1;
	if (!path)
		return ;
	if (path[0])
	{
		ft_dprintf(g_fd, "Shortest path len %d :\n", path[0]->len);
		while (path[++i])
		{
			tmp = path[i];
			ft_dprintf(g_fd, "path n %d: len %d:\n", i, path[i]->len);
			while (tmp)
			{
				ft_dprintf(g_fd, "%d(%s) |", tmp->i, adlist[tmp->i]->name);
				tmp = tmp->next;
			}
			ft_dprintf(g_fd, "\n");
		}
	}
	else
		ft_dprintf(g_fd, "START is connected to END\n");
	ft_dprintf(g_fd, "\n");
	ft_dprintf(g_fd, "\n");
}

void	print_matrix(int **matrix, int size)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	ft_dprintf(g_fd, "    ");
	while (++i < size)
		ft_dprintf(g_fd, " %3d ", i);
	ft_dprintf(g_fd, "\n");
	i = -1;
	while (++j < size)
	{
		ft_dprintf(g_fd, "%2d  |", j);
		while (++i < size)
			ft_dprintf(g_fd, "[%2d] ", matrix[j][i]);
		i = -1;
		ft_dprintf(g_fd, "\n");
	}
	ft_dprintf(g_fd, "\n");
}
