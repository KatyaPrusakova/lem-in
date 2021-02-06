/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/06 14:05:25 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


void	remove_link(t_graph *graph, int src, int dst)
{
	t_room	*tmp;
	t_room	*prev;

	ft_printf("remove %d\n", dst);
	tmp = graph->adlist[src];
	while (tmp->index != dst)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp->index)
	{
		prev->next = tmp->next;
		ft_memdel((void**)&tmp);
	}
}

/*
** Remove the links used in the shortest path of the graph.
** The first and the last link are not removed.
*/

void	reverse_path(t_path *head, t_graph *graph)
{
	if (!head)
		return;
	head = head->next;
	while (head->next && head->next->next)
	{
		remove_link(graph, head->i, head->next->i);
		head = head->next;
	}
}

/*
** Allocate memroy for visited array. Initializing all values to -1.
*/

int		*init_visited(int room_count)
{
	int	*visited;
	int	i;

	visited = ft_memalloc(sizeof(int) * room_count);
//	if (!visited)
//		ft_error(2);
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
	int		len;

//	ft_printf("shortest path");
	while (q.head)
		dequeue(&q);
	tmp = NULL;
	len = -1;
	while (end_index)
	{
		head = ft_memalloc(sizeof(t_path));
//		if (!head)
//			ft_error(2);
		head->i = end_index;
		head->next = tmp;
		tmp = head;
		end_index = visited[end_index];
		len++;
	}
	head = ft_memalloc(sizeof(t_path));
	head->next = tmp;
	head->len = len;
	ft_memdel((void**)&visited);
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

	ft_bzero(&q, sizeof(t_queue));
	visited = init_visited(graph->room_total);
//	ft_printf("end room e value %d", graph->adlist[5]->e);
	current = graph->adlist[0];
	while(1)
	{
		tmp = graph->adlist[current->index]->next;
//		printf("current %d\n", current->index);
		// What if q is empty?
		while (tmp)
		{
//			printf("tmp index %d", tmp->index);
			if (visited[tmp->index] < 0)
				enqueue(tmp->index, &q, graph->adlist, current->index);
			tmp = tmp->next;
		}
		visited[current->index] = current->prev_room_index;
		if (current->e)
		{
//			ft_printf("end?");
			break;
		}
		//segfault here. Enqueue returns null.
//		ft_memdel((void**)current);
		current = ft_memdup(q.head, sizeof(t_room));
		dequeue(&q);
	}
	return (shortest_path(q, visited, graph->room_total - 1));
}

/*
** Returns the possible paths, starting from the shortest path[0].
**
*/

// <test

void	print_path(t_path *path)
{
	ft_printf("Shortest path len %d :\n", path->len);
	while (path)
	{
		ft_printf("%d |", path->i);
		path = path->next;
	}
	ft_n(1);
}

// test>

int		**find_paths(t_graph *graph)
{
	t_path		**paths;

	paths = ft_memalloc(sizeof(t_path*) * graph->room_total);
//	if (!paths)
//		ft_error(2);
	paths[0] = first_bfs(graph);
	print_path(paths[0]);
// remove the shortest paths links from the graph;
	reverse_path(paths[0], graph);

	return(NULL);
}
