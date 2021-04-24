/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:25:06 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/24 14:17:34 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Checking if the current node is connected to the end node.
*/

int		end_is_neighbour(t_room *head, int end)
{
	while (head)
	{
		if (head->index == end)
			return (1);
		head = head->next;
	}
	return (0);
}

int		check_flow(t_room *src, t_room *dst, int max_flow, t_graph *g)
{
	int flow;
	int out;

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

void	visit_room_new(t_search s, t_graph *graph, int max_flow)
{
	t_room	*tmp;

	if (s.visited[s.room->index] != -1)
		return;
	s.visited[s.room->index] = s.room->prev_room_index;
	tmp = s.room->next;
	while (tmp)
	{
		if (s.visited[tmp->index] == -1 && check_flow(s.room, tmp, max_flow, graph)\
		&& (!is_queued(tmp->index, s.q) || tmp->index == s.end))
			enqueue(tmp->index, s.q, graph->adlist, s.room->index);
		tmp = tmp->next;
	}
	if(graph->visualize)
		visualize_search(graph, s.room, s.q, graph->weight_m);
}

t_path			*bfs_new(t_graph *g, int start, int end)
{
	t_search s;

	if (g->visualize)
		ft_printf("SEARCH\n");
	s = init_search(g, start, end);
	while (!s.path && s.q->head)
	{
		s.room = ft_memdup((void*)g->adlist[s.q->head->index], sizeof(t_room));
		if (!s.room)
			print_error(2, NULL);
		s.room->prev_room_index = s.q->head->prev_room_index;
		dequeue(s.q);
		if (s.room->index == s.end)
			s.path = save_path(s.visited, g, s, s.room->prev_room_index);
		else
			visit_room_new(s, g, 0);
		ft_memdel((void**)&s.room);
	}
	return (s.path);
}


t_search		init_search(t_graph *g, int start, int end)
{
	t_search search;
	int i;

	i = 0;
	search.path = NULL;
	search.q = NULL;
	search.visited = ft_memalloc(sizeof(int) * g->room_total * 2);
	if (!search.visited)
		exit(0);
	search.set = ft_memalloc(sizeof(t_path*) * (g->max_paths + 1));
	if (!search.set)
		exit(0);
	search.path_no = 0;
	search.q = enqueue(start, search.q, g->adlist, 0);
	search.start = start;
	search.end = end;
	while (i < g->room_total * 2)
	{
		search.visited[i] = -1;
		i++;
	}
	return (search);
}

t_path	**bfs_set(t_graph *graph, int start, int end)
{
	t_search	s;

	if (graph->visualize)
		ft_printf("BFS\n");
	s = init_search(graph, start, end);
	while (s.q->head && s.path_no < graph->max_paths)
	{
		s.room = ft_memdup(graph->adlist[s.q->head->index], sizeof(t_room));
		s.room->prev_room_index = s.q->head->prev_room_index;
		if (s.q->head)
			dequeue(s.q);
		if (s.room->index == s.end)
		{
			if (!check_path(graph, s, &s.path_no, s.room->prev_room_index))
				return (s.set);
		}
		else
			visit_room_new(s, graph, 1);
		ft_memdel((void**)&s.room);
	}
	if (!s.path_no || !s.set[0])
		return (NULL);
	else
		return (s.set);
}

