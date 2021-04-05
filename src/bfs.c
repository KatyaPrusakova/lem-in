/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:25:06 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/01 21:23:50 by ksuomala         ###   ########.fr       */
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
	{
		visited_to_visualizer(current->index, current->prev_room_index, 1);
		queue_to_visualizer(graph->adlist, q, 1);
	}
	//test
	ft_dprintf(fd, "\n");
	for (int i = 0; i < graph->room_total; i++)
	{
		ft_dprintf(fd, "|%d", visited[i]);
	}
	ft_dprintf(fd, "|\n");
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
			visited_to_visualizer(room->index, room->prev_room_index, graph->visualize);
			queue_to_visualizer(graph->adlist, q, graph->visualize);
			visited[room->index] = room->prev_room_index;
			return (save_path(visited, room->index, graph->room_total - 1));
		}
		else
			visit_room(room, q, visited, graph, edge_w);
		ft_memdel((void**)&room);
	}
	return (NULL);
}
