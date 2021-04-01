/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:34:07 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/01 13:40:03 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** The path is saved in the *visited array. visited[room->index] contains
** the index of the room it was visited from. Returns the found path as
** a linked list.
*/

t_path		*save_path(int *visited, int link_index, /*int **matrix, */int end_room)
{
	t_path	*head;
	t_path	*tmp;
	int		prev;
	int		len;

	ft_dprintf(fd, "path found at %d\n", link_index); //test
//	ft_printf("shortest path");

//What if start is directly linked to end?
	if (!link_index)
		return(NULL);
	tmp = NULL;
	len = 0;
	head = ft_memalloc(sizeof(t_path));
	if (!head)
		ft_printf("error");
	head->i = end_room;
	head->next = NULL;
	tmp = head;
	while (link_index)
	{
		//leaking
		if (link_index == -2)
			return NULL;
		else
		{
			prev = visited[link_index];
			visited[link_index] = -2;
		}
		head = ft_memalloc(sizeof(t_path));
//		if (!head)
//			ft_error(2);
		head->i = link_index;
		head->next = tmp;
		tmp = head;
		link_index = prev;
		ft_dprintf(fd, "- %d -", link_index); //test
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
	return (head);
}

/*
** Check if any of the rooms in the found path are already used on a saved
** path. If not, save the path, and return the paths array. Otherwise return
** path array unmodified.
*/



t_path **check_path(t_graph *graph, int *visited, int link_index, t_path **set, int *path_no)
{
	t_path	*found_path;

//if visualize
//	ft_printf("%d %d %d\n%d-%d\n", link_index, visited[link_index],
//	graph->weight_m[visited[link_index]][link_index], link_index, link_index);
	found_path = save_path(visited, link_index, graph->room_total - 1);
	if (!found_path)
		return (set);
	ft_dprintf(fd, "path saved in [%d]\n", *path_no);
	set[*path_no] = found_path;
	*path_no += 1;
	return (set);
}
