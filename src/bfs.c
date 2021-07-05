/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:25:06 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 17:49:35 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	check_flow(t_room *src, t_room *dst, int max_flow, t_graph *g)
{
	int	flow;
	int	out;

	flow = g->weight_m[src->index][dst->index];
	out = src->out;
	if (max_flow && flow == max_flow)
		return (1);
	else if (!max_flow && out && !flow)
		return (1);
	else if (!max_flow && !out && flow == -1)
		return (1);
	else if (!out && dst->index == src->index + g->room_total && !flow)
		return (1);
	else
		return (0);
}

t_search	visit_room(t_search s, t_graph *graph, int max_flow)
{
	t_room	*tmp;

	if (s.visited[s.room.index] != -1)
		return (s);
	s.visited[s.room.index] = s.room.prev_room_index;
	tmp = s.room.next;
	while (tmp)
	{
		if (s.visited[tmp->index] == -1 && check_flow(&s.room, \
		tmp, max_flow, graph))
		{
			s.q = enqueue(tmp->index, s.q);
			graph->adlist[tmp->index]->prev_room_index = s.room.index;
		}
		tmp = tmp->next;
	}
	if (graph->visualize)
		visualize_search(s.visited, graph, &s.room, graph->weight_m);
	return (s);
}

t_path	*bfs(t_graph *g, int start, int end)
{
	t_search	s;

	s = init_search(g, start, end);
	while (!s.path && s.q->len)
	{
		s.room = *g->adlist[s.q->data[s.q->head]];
		dequeue(s.q);
		if (s.room.index == s.end)
		{
			s.path = save_path(s.visited, g, s, s.room.prev_room_index);
			if (g->visualize)
				path_to_visualizer(s.path, g->room_total, 1);
		}
		else
			s = visit_room(s, g, 0);
	}
	ft_memdel((void **)&s.visited);
	ft_free2d((void **)s.set);
	free_queue(s.q);
	return (s.path);
}

t_search	init_search(t_graph *g, int start, int end)
{
	t_search	search;
	int			i;

	i = 0;
	search.path = NULL;
	search.q = NULL;
	search.visited = ft_memalloc(sizeof(int) * g->room_total * 2);
	if (!search.visited)
		print_error(2, NULL);
	search.set = ft_memalloc(sizeof(t_path *) * (g->max_paths + 1));
	if (!search.set)
		print_error(2, NULL);
	search.path_no = 0;
	search.q = enqueue(start, search.q);
	search.start = start;
	search.end = end;
	while (i < g->room_total * 2)
	{
		search.visited[i] = -1;
		i++;
	}
	return (search);
}

/*
** Doing BFS in a loop and saving all the paths until the queue is empty.
** The paths are not allowed to use the same rooms.
*/

t_path	**bfs_set(t_graph *graph, int start, int end)
{
	t_search	s;

	s = init_search(graph, start, end);
	while (s.q->len && s.path_no < graph->max_paths)
	{
		s.room = *graph->adlist[s.q->data[s.q->head]];
		if (s.q->len)
			dequeue(s.q);
		if (end_is_neighbour(&s.room, s.end))
		{
			s.visited[s.room.index] = s.room.prev_room_index;
			if (!check_path(graph, s, &s.path_no, s.room.index))
				s.path_no = graph->max_paths;
		}
		else
			s = visit_room(s, graph, 1);
	}
	ft_memdel((void **)&s.visited);
	free_queue(s.q);
	if (!s.path_no || !s.set[0])
		return (NULL);
	else
		return (s.set);
}
//gnl empty line