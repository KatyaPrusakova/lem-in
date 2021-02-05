/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/05 21:26:42 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"



int		*init_visited(size_t room_count)
{
	int	*visited;

	visited = ft_memalloc(sizeof(int) * room_count);
	if (!visited)
		ft_error(2);
	return (visited);
}

/*
** bfs to find the shortest path from start to end.
** visited array is initialized to 0. If visited[index] > 0, the value is
** the index to the node it was visited from.
*/

int		*shortest_path(t_graph *graph)
{
	t_queue		q;
	t_room		*current;
	t_room		*tmp;
	int			*visited;
	int			i;

	i = 0;
	visited = init_visited(graph->room_total);
	while(i < graph->room_total)
	{
		current = graph->adlist[i];
		tmp = current->next;
		while (tmp)
		{
			if (!visited[tmp->index])
				enqueue(tmp->index, &q, graph->adlist, current->index);
			tmp = tmp->next;
		}
	}
}

/*
** Returns the possible paths, starting from the shortest path[0].
**
*/

int		**find_paths(t_graph *graph)
{
	int		**paths;

	paths = ft_memalloc(sizeof(int*) * graph->room_total);
	if (!paths)
		ft_error(2);
	paths[0] = shortest_path(graph);
}
