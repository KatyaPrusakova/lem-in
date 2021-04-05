/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_weight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:30:46 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/01 16:40:03 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Checks that the edge weight is the one that should be used in the current
** search.
*/

int		check_weight(int link_weight, int set_weight)
{
	if (set_weight == 1 && link_weight < 1)
		return (1);
	else if (set_weight == 2 && link_weight == 1)
		return (1);
	else if (set_weight == 3 && !link_weight)
		return (1);
	else
		return (0);
}

/*
** Modify the edge weight values of the graph when a path is found.
** If the path is in use, all the edges of the rooms along the path will be closed
** with a value of 3.
*/

int		**mod_edgeweight_path(int **matrix, t_path *path, t_graph *g, int path_is_used)
{
	t_room *tmp;
	if (!path)
		return (matrix);
	while (path->next)
	{
		if (path_is_used)
		{
			if (!path->i)
				path = path->next;
			tmp = g->adlist[path->i]->next;
			while (tmp)
			{
				matrix[path->i][tmp->index] = 3;
				matrix[tmp->index][path->i] = 3;
				tmp = tmp->next;
			}
		}
		else
		{
			matrix[path->i][path->next->i] += 1;
			matrix[path->next->i][path->i] -= 1;
		}
			path = path->next;
	}
	return (matrix);
}
