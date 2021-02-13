/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/13 12:13:12 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Removes a link node from the adlist.
*/

void	remove_link(t_graph *graph, int src, int dst)
{
	t_room	*tmp;
	t_room	*prev;

	ft_dprintf(fd, "remove %d\n", dst); //test
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
** Removes the links used in the shortest path of the graph.
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
	visited[0] = 0;
	return (visited);
}

/*
** The path is saved in the *visited array. visited[room->index] contains
** the index of the room it was visited from. Returns the found path as
** a linked list.
*/

t_path		*save_path(int *visited, int end_index)
{
	t_path	*head;
	t_path	*tmp;
	int		len;

	ft_dprintf(fd, "path found at %d\n", end_index); //test
//	ft_printf("shortest path");
	if (!end_index)
		return(NULL);
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
		ft_dprintf(fd, "- %d -", end_index); //test
		len++;
	}
	head = ft_memalloc(sizeof(t_path));
	head->next = tmp;
	head->len = len;
	return (head);
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
** Prints the current state of queue to stdout.
*/

void	draw_queue(t_room **adlist, t_queue *q)
{
	t_room	*tmp;

	if (!adlist)
		ft_printf("unused variable");
	tmp = q->head;
	if (!q || !tmp)
	{
		return;
	}
	while (tmp)
	{
		ft_printf("%d-%d\n", tmp->prev_room_index, tmp->index);
		tmp = tmp->next;
	}
}

/*
** Saving the current room as visited, and the index of the room it was visited
** from. Adds the linked rooms to the queue.
*/

void	visit_room(t_room *current, t_queue *q, int *visited, t_graph *graph)
{
	t_room	*tmp;

	visited[current->index] = current->prev_room_index;
	tmp = current->next;
	while (tmp)
	{
		if (visited[tmp->index] < 0)
			enqueue(tmp->index, q, graph->adlist, current->index);
		tmp = tmp->next;
	}
	if(graph->visualize)
	{
		ft_printf("%d %d\n", current->index, current->prev_room_index);
		draw_queue(graph->adlist, q);
	}
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

t_path	**bfs(int max_paths, t_graph *graph, t_room	*room, int visualize)
{
	t_path	**set_1;
	t_queue	*q;
	t_room	*tmp;
	int		*visited;
	int		i;

	i = -1;
	q = NULL;
	if (visualize)
		ft_dprintf(fd, "use visualizer\n"); //test
	visited = init_visited(graph->room_total);
	set_1 = ft_memalloc(sizeof(t_path*) * max_paths);
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
		if (end_is_neighbour(tmp))
		{
			visited[room->index] = room->prev_room_index;
			set_1[++i] = save_path(visited, room->index);
		}
		else
			visit_room(room, q, visited, graph);
		ft_memdel((void**)&room);
	}
	if (graph->visualize)
		ft_printf("START_ANT_MOVEMENT\n");
	return (set_1);
}

/*
** Returns the possible paths, starting from the shortest path[0].
*/

// <test

void	print_paths(t_path **path)
{
	t_path *tmp;
	int	i = -1;
	if (path[0])
	{
		ft_dprintf(fd, "Shortest path len %d :\n", path[0]->len);
		while (path[++i])
		{
			tmp = path[i];
			ft_dprintf(fd, "path n %d: ", i);
			while (tmp)
			{
				ft_dprintf(fd, "%d |", tmp->i);
				tmp = tmp->next;
			}
			ft_dprintf(fd, "\n");
		}
	}
	else
		ft_dprintf(fd, "START is connected to END\n");
}

// test>

/*
** Counts the maximum amount of needed paths. Maximum path count is the
** min amount of rooms linked to start or end rooms.
*/

int		count_paths(t_graph *graph)
{
	t_room	*tmp;
	int		start;
	int		end;

	start = 0;
	end = 0;
	tmp = graph->adlist[0];
	while (tmp->next)
	{
		tmp = tmp->next;
		start++;
	}
	tmp = graph->adlist[graph->room_total - 1];
	while (tmp->next)
	{
		tmp = tmp->next;
		end++;
	}
	start = (start < end) ? start : end;
	return (start);
}

int		**find_paths(t_graph *graph)
{
	t_path		**paths;
	int			max_paths;

	max_paths = count_paths(graph);
	paths = ft_memalloc(sizeof(t_path*) * graph->room_total);
//	if (!paths)
//		ft_error(2);
	paths = bfs(max_paths, graph, graph->adlist[0], graph->visualize);
	ft_dprintf(fd, "paths found\n");
	print_paths(paths);
// remove the shortest paths links from the graph;
	if (paths[0] && paths[0]->len > 1)
	{
		ft_dprintf(fd, "\nBFS 2.0\n");
		reverse_path(paths[0], graph);
		paths = bfs(max_paths, graph, graph->adlist[0], graph->visualize);
		print_rooms(graph);
	}
//	print_paths(paths);

	return(NULL);
}
