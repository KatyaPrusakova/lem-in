/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_weight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:30:46 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/31 15:47:12 by ksuomala         ###   ########.fr       */
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
*/

int		**mod_edge_weight(int **matrix, t_path *path)
{
	while (path->next)
	{
		matrix[path->i][path->next->i] += 1;
		matrix[path->next->i][path->i] -= 1;
		path = path->next;
	}
	return (matrix);
}
