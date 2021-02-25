/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/25 11:35:20 by eprusako         ###   ########.fr       */
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
	return (visited);
}

/*
** Modify the edge weight values of the graph when a path is found.
*/

int		**mod_edge_weight(int **matrix, t_path *path)
{
	while (path->next)
	{
		matrix[path->i][path->next->i] += 1;
		matrix[path->next->i][path->i] -= 1;
		path = path->next;
	}
	return (matrix);
}

/*
** The path is saved in the *visited array. visited[room->index] contains
** the index of the room it was visited from. Returns the found path as
** a linked list.
*/

t_path		*save_path(int *visited, int find_path, int **matrix, int end_room)
{
	t_path	*head;
	t_path	*tmp;
	int		prev;
	int		len;

	ft_dprintf(fd, "path found at %d\n", find_path); //test
//	ft_printf("shortest path");

	if (!find_path)
		return(NULL);
	tmp = NULL;
	len = -1;
	head = ft_memalloc(sizeof(t_path));
	if (!head)
		ft_printf("error");
	head->i = end_room;
	head->next = NULL;
	tmp = head;
	while (find_path)
	{
		//leaking
		if (find_path == -2)
			return NULL;
		else
		{
			prev = visited[find_path];
			visited[find_path] = -2;
		}
		head = ft_memalloc(sizeof(t_path));
//		if (!head)
//			ft_error(2);
		head->i = find_path;
		head->next = tmp;
		tmp = head;
		find_path = prev;
		ft_dprintf(fd, "- %d -", find_path); //test
		len++;
	}
	head = ft_memalloc(sizeof(t_path));
	head->next = tmp;
	head->len = len;
	tmp = head;
	while (tmp)
	{
		ft_printf("%d |", tmp->i);
		tmp = tmp->next;
	}
	ft_n(1);
	mod_edge_weight(matrix, head);
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
		ft_printf("%d-%d ", tmp->prev_room_index, tmp->index);
		tmp = tmp->next;
	}
	ft_n(1);
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
		ft_printf("%d %d %d\n", current->index, current->prev_room_index,
		graph->weight[current->prev_room_index][current->index]);
		draw_queue(graph->adlist, q);
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
** Check if any of the rooms in the found path are already used on a saved
** path. If not, save the path, and return the paths array. Otherwise return
** path array unmodified.
*/



t_path **check_path(t_graph *graph, int *visited, int find_path, t_path **path, int *path_no)
{
	t_path	*found_path;

	found_path = save_path(visited, find_path, graph->weight, graph->room_total - 1);
	if (!found_path)
		return (path);
	ft_dprintf(fd, "path saved in [%d]\n", *path_no);
	path[*path_no] = found_path;
	*path_no += 1;
	return (path);
}


t_path	**bfs_3(int max_paths, t_graph *graph, t_room	*room, int visualize)
{
	t_path	**set_1;
	t_queue	*q;
	t_room	*tmp;
	int		*visited;
	int		i;

	i = 0;
	q = NULL;
	if (visualize)
		ft_dprintf(fd, "use visualizer\n"); //test
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

t_path	*bfs_2(int max_paths, t_graph *graph, t_room	*room, int visualize)
{
//	t_path	**set_1;
	t_queue	*q;
	t_room	*tmp;
	int		*visited;
	int		i;

	i = 0;
	q = NULL;
	if (visualize)
		ft_dprintf(fd, "use visualizer\n"); //test
	visited = init_visited(graph->room_total);
//	set_1 = ft_memalloc(sizeof(t_path*) * (max_paths));
//	if (!set_1)
//		ft_printf("malloc fail"); //change
	q = enqueue(room->index, q, graph->adlist, 0);
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
			visited[room->index] = room->prev_room_index;
			return (save_path(visited, room->index, graph->weight, graph->room_total - 1));
		}
		else
			visit_room(room, q, visited, graph, 1);
		ft_memdel((void**)&room);
	}
	if (graph->visualize)
		ft_printf("START_ANT_MOVEMENT\n");
	return (NULL);
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
//		ft_dprintf(fd, "Shortest path len %d :\n", path[0]->len);
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

void	print_matrix(int **matrix, int size)
{
	int i;
	int j;

	i = -1;
	j = -1;

	while (++j < size)
	{
		while (++i < size)
			ft_dprintf(fd, "[%d] ", matrix[j][i]);
		i = -1;
		ft_dprintf(fd, "\n");
	}
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
	paths[0] = bfs_2(max_paths, graph, graph->adlist[0], graph->visualize);

//	ft_dprintf(fd, "\npaths found\n");
	print_matrix(graph->weight, graph->room_total);
	paths[0] = bfs_2(max_paths, graph, graph->adlist[0], graph->visualize);
	paths = bfs_3(max_paths, graph, graph->adlist[0], graph->visualize);

	//print_paths(paths);
	allocate_ants_to_rooms(paths, graph);
// remove the shortest paths links from the graph;
/*	if (paths[0] && paths[0]->len > 1)
	{
		ft_dprintf(fd, "\nBFS 2.0\n");

		reverse_path(paths[0], graph);
		paths = bfs(max_paths, graph, graph->adlist[0], graph->visualize);
		print_rooms(graph);
	} */
//	print_paths(paths);

	return(NULL);
}