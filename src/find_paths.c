/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:57:57 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/02 17:21:55 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** This is the parent function of our path-finding algorithm. 0 will be the
** shortest path and the last one the longest.
*/

int		*shortest_path(t_graph *graph)
{
	int		*path;
	t_room	*current;

	path = ft_memalloc(sizeof(int) * graph->room_total);
	if (!path)
		ft_error("malloc fail");
	current = graph->adlist[0];
	while (current)
	{
		f
	}
}

int		**find_paths(t_graph *graph)
{
	int		**paths;
	int		count;

	paths = ft_memalloc(sizeof(int*) * graph->room_total);
	if (!paths)
		ft_error("malloc fail");
	paths[0] = shortest_path(graph);
}
