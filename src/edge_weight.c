/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_weight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:30:46 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/25 13:01:48 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Checks that the edge weight is the one that should be used in the current
** search.
*/

int			check_weight(int link_weight, int set_weight)
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
** Modify the edges along a found path.
*/

void		mod_edgeweight_path(t_graph *g, t_path *path)
{
	if (!path)
		return ;
	while (path->next)
	{
		g->weight_m[path->i][path->next->i] += 1;
		g->weight_m[path->next->i][path->i] -= 1;
		path = path->next;
	}
}
