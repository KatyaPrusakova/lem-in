/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:25:06 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/21 19:16:42 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Allocate memroy for visited array. Initializing start node value to 0 and all
** other values to -1.
*/

// int		*init_visited(int room_count)
// {
// 	int	*visited;
// 	int	i;

// 	visited = ft_memalloc(sizeof(int) * room_count);
// //	if (!visited)
// //		ft_error(2);
// 	i = 0;
// 	while (i < room_count)
// 	{
// 		visited[i] = -1;
// 		i++;
// 	}
// 	return (visited);
// }

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

void	queue_neighbours(t_search s, t_graph *g, int edge_w)
{
	t_room *tmp;

	tmp = s.room->next;
	ft_printf("queue %d : tmp->index%d\n", s.room->index, tmp->index);
	while(tmp)
	{
		if (s.visited[tmp->index == -1 && check_weight(g->weight_m[s.room->index][tmp->index], edge_w)] && tmp->index != s.end)
			enqueue(tmp->index, s.q, g->adlist, s.room->index);
		tmp = tmp->next;
	}
}

/*
** Saving the current room as visited, and the index of the room it was visited
** from. Adds the linked rooms to the queue.
*/

void	visit_room(t_room *current, t_queue *q, int *visited, t_graph *graph, int set_weight)
{
	t_room	*tmp;

	if (visited[current->index] != -1)
		return;
	visited[current->index] = current->prev_room_index;
//	graph->adlist[current->index]->next = adlist_mergesort(current->next, current->index, graph->weight_m);
	tmp = current->next;
	while (tmp)
	{
		if (visited[tmp->index] == -1 && check_weight(graph->weight_m[current->index][tmp->index],\
		set_weight))
			enqueue(tmp->index, q, graph->adlist, current->index);
		tmp = tmp->next;
	}
	if(graph->visualize)
		visualize_search(current, q, graph->weight_m);
		//test
//	ft_dprintf(fd, "\n");
	// for (int i = 0; i < graph->room_total; i++)
	// {
	// 	ft_dprintf(fd, "|%d", visited[i]);
	// }
	// ft_dprintf(fd, "|\n");
}

t_path		*bfs(t_graph *g, int edge_w, int start, int end)
{
	t_search s;

	if (g->visualize)
		ft_printf("BFS\n");
	s = init_search(g, start, end);
	while (!s.path && s.q->head)
	{
		s.room = ft_memdup((void*)g->adlist[s.q->head->index], sizeof(t_room));
		s.room->prev_room_index = s.q->head->prev_room_index;
		if (!s.room)
			print_error(2, NULL);
		dequeue(s.q);
		if (end_is_neighbour(s.room, end) && check_weight(g->weight_m[s.room->index][end], edge_w))
		{
			s.visited[s.room->index] = s.room->prev_room_index;
			s.path = save_path(s.visited, s.room->index, g, s);
		}
		else
			visit_room(s.room, s.q, s.visited, g, edge_w);
		free(s.room);
		s.room = NULL;
	}
	return (s.path);
}

/*
** Traversing through the graph using BFS, until all the rooms are visited
** or the max_paths amount of paths is found(the amount of rooms linked to start or end).
**
** Int array *visited is used to track which rooms have been visited. Values are initialized
** to -1. When a room is visited, visited[room->index] is set to the index of the previous
** room.
**
** edge_w variable defines which links can be used. First two searches use edges
** with values < 1.Third search uses edges with value of 1.
*/


/*t_path	*bfs(t_graph *graph, int edge_w)
{
	t_queue	*q;
	t_room	*tmp;
	t_room	*room;
	int		*visited;

	q = NULL;
	visited = init_visited(graph->room_total);
	q = enqueue(0, q, graph->adlist, 0);
	while (q->head)
	{
		room = ft_memdup(graph->adlist[q->head->index], sizeof(t_room));
		room->prev_room_index = q->head->prev_room_index;
		if (q->head)
			dequeue(q);
		tmp = room->next;
		if (end_is_neighbour(tmp, graph->room_total - 1) && visited[room->index] == -1 && \
		check_weight(graph->weight_m[room->index][graph->room_total - 1], edge_w))
		{
			if (graph->visualize)
				visualize_search(room, q);
			visited[room->index] = room->prev_room_index;
			return (save_path(visited, room->index, graph, ));
		}
		else
			visit_room(room, q, visited, graph, edge_w);
		ft_memdel((void**)&room);
	}
	return (NULL);
} */

/*
**initializes variables used in bfs_set and returns the visited int array.
** Creates visited array, enqueues the first room.
*/

t_search		init_search(t_graph *g, int start, int end)
{
	t_search search;
	int i;

	i = 0;
//	search.continue_alternative_edges = 0;
//	if (mod_edge == 3)
//		search.continue_alternative_edges = 1;
	search.path = NULL;
	search.q = NULL;
	search.visited = ft_memalloc(sizeof(int) * g->room_total);
	if (!search.visited)
		exit(0);
	search.set = ft_memalloc(sizeof(t_path*) * (g->max_paths + 1));
	if (!search.set)
		exit(0);
	search.path_no = 0;
	search.q = enqueue(start, search.q, g->adlist, 0);
	search.start = start;
	search.end = end;
	while (i < g->room_total)
	{
		search.visited[i] = -1;
		i++;
	}
	return (search);
}
/*
** BFS that finds a full set of paths and modifies the edge values.
*/


t_path	**bfs_set(t_graph *graph, int edge_w, int start, int end)
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
		if (end_is_neighbour(s.room->next, end) && s.visited[s.room->index] == -1 && \
		check_weight(graph->weight_m[s.room->index][graph->room_total - 1], edge_w))
		{
			if (!check_path(graph, s, s.room->index, &s.path_no))
				return (s.set);
		}
		else
			visit_room(s.room, s.q, s.visited, graph, edge_w);
		ft_memdel((void**)&s.room);
	}
	if (!s.path_no || !s.set[0])
		return (NULL);
	else
		return (s.set);
}


t_path	**bfs_set_weightend(t_graph *graph, int edge_w, int start, int end)
{
	t_search	s;

	if (graph->visualize)
		ft_printf("BFS\n");
	s = init_search(graph, start, end);
	s.tmp = graph->adlist[s.start]->next;
	while (s.tmp)
	{
		enqueue(s.tmp->index, s.q, graph->adlist, s.start);
		s.tmp = s.tmp->next;
	}
	while (s.q->head && s.path_no < graph->max_paths)
	{
		s.room = ft_memdup(graph->adlist[s.q->head->index], sizeof(t_room));
		s.room->prev_room_index = s.q->head->prev_room_index;
		if (s.q->head)
			dequeue(s.q);
		if (end_is_neighbour(s.room->next, end) && s.visited[s.room->index] == -1)
		{
			if (!check_path(graph, s, s.room->index, &s.path_no))
				return (s.set);
		}
		else
			visit_room(s.room, s.q, s.visited, graph, edge_w);
		ft_memdel((void**)&s.room);
	}
	if (!s.path_no || !s.set[0])
		return (NULL);
	else
		return (s.set);
}


int			bfs_set_modify(t_graph *graph, int edge_w, int start, int end)
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
		s.tmp = s.room->next;
		if (end_is_neighbour(s.tmp, graph->room_total - 1) && s.visited[s.room->index] == -1
		&& check_weight(graph->weight_m[s.room->index][s.end], edge_w))
		{
			// find paths
			// only modify the paths when all of them have been found
			// also check neighbours and alternative paths from the room that is connected to the end room
			if (graph->visualize)
				ft_printf("end is neighbour %d\n", s.room->index);
			check_path(graph, s, s.room->index, &s.path_no);
			visit_room(s.room, s.q, s.visited, graph, edge_w);

			queue_neighbours(s, graph, edge_w);
		}
		else
			visit_room(s.room, s.q, s.visited, graph, edge_w);
		ft_memdel((void**)&s.room);
	}
	if (!s.path_no || !s.set[0])
		return (0);
	else
	{
		mod_edgeweight_set(graph, s.set);
		return (1);
	}
}
