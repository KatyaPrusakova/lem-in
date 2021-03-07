/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:34:07 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/02 17:16:20 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"



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
	len = 0;
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
** Check if any of the rooms in the found path are already used on a saved
** path. If not, save the path, and return the paths array. Otherwise return
** path array unmodified.
*/



t_path **check_path(t_graph *graph, int *visited, int find_path, t_path **path, int *path_no)
{
	t_path	*found_path;

//if visualize
//	ft_printf("%d %d %d\n%d-%d\n", find_path, visited[find_path],
//	graph->weight[visited[find_path]][find_path], find_path, find_path);
	found_path = save_path(visited, find_path, graph->weight, graph->room_total - 1);
	if (!found_path)
		return (path);
	ft_dprintf(fd, "path saved in [%d]\n", *path_no);
	path[*path_no] = found_path;
	*path_no += 1;
	return (path);
}
