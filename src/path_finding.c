/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/07 14:35:49 by ksuomala         ###   ########.fr       */
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
	visited[0] = 0;
	return (visited);
}

/*
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
*/

t_path		*save_path(int *visited, int end_index)
{
	t_path	*head;
	t_path	*tmp;
	int		len;

	ft_printf("path found at %d\n", end_index);
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
		ft_printf("- %d -", end_index);
		len++;
	}
	head = ft_memalloc(sizeof(t_path));
	head->next = tmp;
	head->len = len;
	return (head);
}

/*
** bfs to find the shortest path from start to end.
** visited array is initialized to -1. If visited[index] > -1, the value is
** the index to the node it was visited from.
*/

/*
t_path		**first_bfs(t_graph *graph, int connections)
{
	t_queue		q;
	t_path		**set_1;
	t_room		*current;
	t_room		*tmp;
	int			*visited;

	if (connections) //use var
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
			if (graph->adlist[tmp->index]->e)
			{

				dequeue(&q);
			}
			tmp = tmp->next;
		}
		visited[current->index] = current->prev_room_index;
		if (current->e)
		{
			set_1 =
		}
		ft_memdel((void**)current);
		current = ft_memdup(q.head, sizeof(t_room));
		dequeue(&q);
	}
//	return (shortest_path(q, visited, graph->room_total - 1));
}
*/

/*
** Checking if the current node is connected to the end node.
*/

int		end_is_neighbour(t_room *head)
{
	while (head)
	{
		if (head->e)
			return (1);
		head = head->next;
	}
	return (0);
}

void	visit_room(t_room *current, t_queue *q, int *visited, t_room **adlist)
{
	t_room	*tmp;

	visited[current->index] = current->prev_room_index;
	tmp = current->next;
	while (tmp)
	{
		if (visited[tmp->index] < 0)
			enqueue(tmp->index, q, adlist, current->index);
		tmp = tmp->next;
	}
}

t_path	**bfs(int max_paths, t_graph *graph, t_room	*room)
{
	t_path	**set_1;
	t_queue	q;
	t_room	*tmp;
	int		*visited;
	int		i;

	i = -1;
	ft_bzero(&q, sizeof(t_queue));
	visited = init_visited(graph->room_total);
	set_1 = ft_memalloc(sizeof(t_path*) * max_paths);
	if (!set_1)
		ft_printf("malloc fail"); //change
	enqueue(room->index, &q, graph->adlist, 0);
	while (q.head && i < max_paths)
	{
		room = ft_memdup(graph->adlist[q.head->index], sizeof(t_room));
		room->prev_room_index = q.head->prev_room_index;
		dequeue(&q);
		tmp = room->next;
		if (end_is_neighbour(tmp))
		{
			visited[room->index] = room->prev_room_index;
			set_1[++i] = save_path(visited, room->index);
		}
		else
			visit_room(room, &q, visited, graph->adlist);
		ft_memdel((void**)&room);
	}
	return (set_1);
}

/*
** Returns the possible paths, starting from the shortest path[0].
**
*/

// <test

void	print_paths(t_path **path)
{
	t_path *tmp;
	int	i = -1;
	if (!path)
	{
		ft_printf("START has a link to END\n");
		return ;
	}
	else
	{
		ft_printf("Shortest path len %d :\n", path[0]->len);
		while (path[++i])
		{
			tmp = path[i];
			ft_printf("path n %d: ", i);
			while (tmp)
			{
				ft_printf("%d |", tmp->i);
				tmp = tmp->next;
			}
			ft_n(1);
		}
	}
}

// test>

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
	paths = bfs(max_paths, graph, graph->adlist[0]);
	ft_printf("paths found\n");
	print_paths(paths);
// remove the shortest paths links from the graph;
	reverse_path(paths[0], graph);

	return(NULL);
}
