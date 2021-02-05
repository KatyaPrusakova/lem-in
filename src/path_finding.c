/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/05 22:41:32 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


/*
** Allocate memroy for visited array. Initializing all values to -1.
*/

int		*init_visited(size_t room_count)
{
	int	*visited;
	int	i;

	visited = ft_memalloc(sizeof(int) * room_count);
	if (!visited)
		ft_error(2);
	i = 0;
	while (i < room_count)
	{
		visited[i] = -1;
		i++;
	}
	return (visited);
}

t_path		*shortest_path(t_queue q, int *visited, int end_index)
{
	t_path	*head;
	t_path	*tmp;

	while (q.head)
		dequeue(&q);
	tmp = NULL;
	while (end_index)
	{
		head = ft_memalloc(sizeof(t_path));
		if (!head)
			ft_error(2);
		head->i = end_index;
		head->next = tmp;
		tmp = head;
		end_index = visited[end_index];
	}
	ft_memdel((void**)visited);
	return (head);
}

/*
** bfs to find the shortest path from start to end.
** visited array is initialized to -1. If visited[index] > -1, the value is
** the index to the node it was visited from.
*/

t_path		*first_bfs(t_graph *graph)
{
	t_queue		q;
	t_room		*current;
	t_room		*tmp;
	int			*visited;

	visited = init_visited(graph->room_total);
	current = graph->adlist[0];
	while(1)
	{
		tmp = current->next;
		while (tmp)
		{
			if (!visited[tmp->index])
				enqueue(tmp->index, &q, graph->adlist, current->index);
			tmp = tmp->next;
		}
		visited[current->index] = current->prev_room_index;
		if (current->e)
			break;
		if (!current->e && !q.head)
			ft_printf("No path from start to end\n");
		current = q.head;
		dequeue(&q);
		shortest_path(q, visited, graph->room_total - 1);
	}

}

/*
** Returns the possible paths, starting from the shortest path[0].
**
*/

int		**find_paths(t_graph *graph)
{
	t_path		**paths;

	paths = ft_memalloc(sizeof(t_path*) * graph->room_total);
	if (!paths)
		ft_error(2);
	paths[0] = first_bfs(graph);
//	print path
	ft_printf("Shortest path:\n");
	while (paths[0])
	{
		ft_printf("%d |", paths[0]->i);
		paths[0] = paths[0]->next;
	}
}
