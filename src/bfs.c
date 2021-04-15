/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:25:06 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/15 15:17:10 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Allocate memroy for visited array. Initializing start node value to 0 and all
** other values to -1.
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

/*
** Checking if the current node is connected to the end node.
*/

int		end_is_neighbour(t_room *head)
{
	while (head)
	{
		if (head->end)
			return (1);
		head = head->next;
	}
	return (0);
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
	tmp = current->next;
	while (tmp)
	{
		if (visited[tmp->index] == -1 && check_weight(graph->weight_m[current->index][tmp->index], set_weight))
			enqueue(tmp->index, q, graph->adlist, current->index);
		tmp = tmp->next;
	}
	if(graph->visualize)
		visualize_search(current, q);
		//test
//	ft_dprintf(fd, "\n");
	// for (int i = 0; i < graph->room_total; i++)
	// {
	// 	ft_dprintf(fd, "|%d", visited[i]);
	// }
	// ft_dprintf(fd, "|\n");
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

t_path	*bfs(t_graph *graph, int edge_w)
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
		if (end_is_neighbour(tmp) && visited[room->index] == -1 && \
		check_weight(graph->weight_m[room->index][graph->room_total - 1], edge_w))
		{
			if (graph->visualize)
				visualize_search(room, q);
			visited[room->index] = room->prev_room_index;
			return (save_path(visited, room->index, graph, graph->room_total - 1));
		}
		else
			visit_room(room, q, visited, graph, edge_w);
		ft_memdel((void**)&room);
	}
	return (NULL);
}

/*
**initializes variables used in bfs_set and returns the visited int array.
*/

t_bfs		init_bfs(t_graph *g)
{
	t_bfs search;
	int i;

	i = 0;
	search.q = NULL;
	search.visited = ft_memalloc(sizeof(int) * g->room_total);
	if (!search.visited)
		exit(0);
	search.set = ft_memalloc(sizeof(t_path*) * (g->max_paths + 1));
	if (!search.set)
		exit(0);
	search.path_no = 0;
	search.q = enqueue(0, search.q, g->adlist, 0);
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


t_path	**bfs_set(t_graph *graph, int edge_w)
{
	t_bfs	s;

	s = init_bfs(graph);
	while (s.q->head && s.path_no < graph->max_paths)
	{
		s.room = ft_memdup(graph->adlist[s.q->head->index], sizeof(t_room));
		s.room->prev_room_index = s.q->head->prev_room_index;
		if (s.q->head)
			dequeue(s.q);
		s.tmp = s.room->next;
		if (end_is_neighbour(s.tmp) && s.visited[s.room->index] == -1 && \
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


/*t_path	**bfs_set_modify(t_graph *graph, int edge_w, t_path **set)
{
	t_queue	*q;
	t_room	*tmp;
	t_room	*room;
	int		*visited;
	int		path_no;

	path_no = 0;
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
		if (end_is_neighbour(tmp) && visited[room->index] == -1 && \
		check_weight(graph->weight_m[room->index][graph->room_total - 1], edge_w))
		{
			if (graph->visualize)
				visualize_search(room, q);
			visited[room->index] = room->prev_room_index;
			check_path(graph, visited, room->index, set, &path_no);
			if (!pathlen_is_optimal(set, path_no - 1, graph->ants))
			{
				set[path_no - 1] = free_path(set[path_no - 1]);
				ft_dprintf(fd, "PATH TOO LONG\n");
				return (set);
			}
		}
		else
			visit_room(room, q, visited, graph, edge_w);
		ft_memdel((void**)&room);
	}
	return (set);
}
*/

// t_path	**bfs_set_modify(t_graph *graph, int edge_w, t_path **set)
// {
// 	t_queue	*q;
// 	t_room	*tmp;
// 	t_room	*room;
// 	t_path	*to_mod;
// 	int		*visited;

// 	q = NULL;
// 	visited = init_visited(graph->room_total);
// 	q = enqueue(0, q, graph->adlist, 0);
// 	while (q->head)
// 	{
// 		room = ft_memdup(graph->adlist[q->head->index], sizeof(t_room));
// 		room->prev_room_index = q->head->prev_room_index;
// 		if (q->head)
// 			dequeue(q);
// 		tmp = room->next;
// 		if (end_is_neighbour(tmp) && visited[room->index] == -1 &&
// 		check_weight(graph->weight_m[room->index][graph->room_total - 1], edge_w))
// 		{
// 			visited_to_visualizer(room->index, room->prev_room_index, graph->visualize);
// 			queue_to_visualizer(graph->adlist, q, graph->visualize);
// 			visited[room->index] = room->prev_room_index;
// 			to_mod = mod_path(visited, room->index, graph->room_total - 1);
// 			mod_edgeweight_path(graph->weight_m,to_mod, graph, 0);
// 		}
// 		else
// 			visit_room(room, q, visited, graph, edge_w);
// 		ft_memdel((void**)&room);
// 	}
// 	return (set);
// }
