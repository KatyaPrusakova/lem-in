/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_weight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:30:46 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/22 13:43:58 by ksuomala         ###   ########.fr       */
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
	else if (set_weight == 2 && link_weight > 0)
		return (1);
	else if (set_weight == 3 && !link_weight)
		return (1);
	else if (set_weight == 4)
		return (1);
	else
		return (0);
}

/*
** Modify the edge weight values of the graph when a path is found.
** If the path is in use, all the edges of the rooms along the path will be closed
** with a value of 3.
*/

void		mod_edgeweight_path(t_graph *g, t_path *path)
{
	if (!path)
		return;
	while (path->next)
	{
//		g->adlist[path->i]->remaining_capacity -= 1;
		g->weight_m[path->i][path->next->i] += 1;
		g->weight_m[path->next->i][path->i] -= 1;
		path = path->next;
	}
}

void		mod_edgeweight_set(t_graph *g, t_path **set)
{
	int i;

	i = 0;
	while (set[i])
	{
		mod_edgeweight_path(g, set[i]);
		i++;
	}
}
