/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:25:06 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/30 17:57:27 by ksuomala         ###   ########.fr       */
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

void	visit_room(t_room *current, t_queue *q, int *visited, t_graph *graph, int if_v)
{
	t_room	*tmp;

	if (visited[current->index] != -1)
		return;
	visited[current->index] = current->prev_room_index;
	tmp = current->next;
	while (tmp)
	{
		if (visited[tmp->index] == -1 && graph->weight[current->index][tmp->index] != if_v)
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

t_path	**bfs_3(int max_paths, t_graph *graph, t_room	*room)
{
	t_path	**set_1;
	t_queue	*q;
	t_room	*tmp;
	int		*visited;
	int		i;

	i = 0;
	q = NULL;
	visited = init_visited(graph->room_total);
	set_1 = ft_memalloc(sizeof(t_path*) * (max_paths + 1));
	if (!set_1)
		ft_printf("malloc fail"); //change
	q = enqueue(room->index, q, graph->adlist, 0);
	while (q->head && i < max_paths)
	{
		room = ft_memdup(graph->adlist[q->head->index], sizeof(t_room));
		room->prev_room_index = q->head->prev_room_index;
		if (q->head)
			dequeue(q);
		tmp = room->next;
		if (end_is_neighbour(tmp) && visited[room->index] == -1 && \
		graph->weight[room->index][graph->room_total - 1] == 1)
		{
			visited[room->index] = room->prev_room_index;
			ft_printf("%d %d\n", room->index, room->prev_room_index);
			ft_printf("0-0\n"); //q?
			set_1 = check_path(graph, visited, room->index, set_1, &i);
		}
		else
			visit_room(room, q, visited, graph, 0);
		ft_memdel((void**)&room);
	}
	if (graph->visualize)
		ft_printf("START_ANT_MOVEMENT\n");
	return (set_1);
}

/*
** Traversing through the graph using BFS, until all the rooms are visited
** or the max_paths amount of paths is found(the amount of rooms linked to start or end).
**
** Int array *visited is used to track which rooms have been visited. Values are initialized
** to -1. When a room is visited, visited[room->index] is set to the index of the previous
** room.
**
** If the current room is linked to the end room, The path will be saved in the 2d array.
*/

t_path	*bfs(int max_paths, t_graph *graph)
{
	t_queue	*q;
	t_room	*tmp;
	t_room	*room;
	int		*visited;
	int		i;

	i = 0;
	q = NULL;
	visited = init_visited(graph->room_total);
	q = enqueue(0, q, graph->adlist, 0);
	while (q->head && i < max_paths)
	{
		room = ft_memdup(graph->adlist[q->head->index], sizeof(t_room));
		room->prev_room_index = q->head->prev_room_index;
		if (q->head)
			dequeue(q);
		tmp = room->next;
		if (end_is_neighbour(tmp) && visited[room->index] == -1 && \
		graph->weight[room->index][graph->room_total - 1] < 1)
		{
			visited_to_visualizer(room->index, room->prev_room_index, graph->visualize);
			queue_to_visualizer(graph->adlist, q, graph->visualize);
			visited[room->index] = room->prev_room_index;
			return (save_path(visited, room->index, graph->weight, graph->room_total - 1));
		}
		else
			visit_room(room, q, visited, graph, 1);
		ft_memdel((void**)&room);
	}
	return (NULL);
}
