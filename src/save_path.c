/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:34:07 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/22 17:21:50 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** The path is saved in the *visited array. visited[room->index] contains
** the index of the room it was visited from. Returns the found path as
** a linked list.
*/

t_path		*save_path(int *visited, int edge_index, t_graph *g, t_search s)
{
	t_path	*head;
	t_path	*tmp;
	int		prev;
	int		len;

//What if start is directly linked to end?
	if (!edge_index)
		return(NULL);
	tmp = NULL;
	len = 0;
	head = ft_memalloc(sizeof(t_path));
	if (!head)
		ft_printf("error");
	head->i = s.end;
	head->name = g->adlist[s.end]->name;
	head->next = NULL;
	tmp = head;
	while (edge_index != s.start)
	{
		//leaking
		if (edge_index == -2)
		{
			ft_dprintf(fd, "link index == -2\n");
			return NULL;
		}
		else
		{
			prev = visited[edge_index];
		//	visited[edge_index] = -2;
		}
		head = ft_memalloc(sizeof(t_path));
//		if (!head)
//			ft_error(2);
		head->i = edge_index;
		head->name = g->adlist[edge_index]->name;
		head->next = tmp;
		tmp = head;
		edge_index = prev;
	//	ft_dprintf(fd, "- %d -", edge_index); //test
		len++;
	}
	head = ft_memalloc(sizeof(t_path));
	head->next = tmp;
	head->len = len;
	tmp = head;
	if (g->visualize)
	{
		while (tmp)
		{
			ft_printf("%d |", tmp->i);
			tmp = tmp->next;
		}
		ft_n(1);
	}
	return (head);
	}

void	modify_visited_array(int *visited, t_path *path)
{
	path = path->next;
	while (path)
	{
		visited[path->i] = -2;
		path = path->next;
	}
}

/*
** Check if any of the rooms in the found path are already used on a saved
** path. If not, save the path, and return the paths array. Otherwise return
** path array unmodified.
*/



int		check_path(t_graph *graph, t_search s, int edge_index, int *path_no)
{
	t_path	*found_path;

	if (graph->visualize)
		visualize_search(graph, s.room, s.q, graph->weight_m);
	s.visited[s.room->index] = s.room->prev_room_index;
	found_path = save_path(s.visited, edge_index, graph, s);
	if (!found_path)
	{
		ft_dprintf(fd, "NULL path\n"); //test
		return (1);
	}
	s.set[*path_no] = found_path;
	*path_no += 1;
	if (!pathlen_is_optimal(s.set, *path_no - 1, graph->ants))
	{
		s.set[*path_no - 1] = free_path(s.set[*path_no - 1]);
		ft_dprintf(fd, "PATH TOO LONG\n");
		return (0);
	}
	return (1);
}

t_path		*mod_path(int *visited, int edge_index, /*int **matrix, */int end_room)
{
	t_path	*head;
	t_path	*tmp;
	int		prev;
	int		len;

//What if start is directly linked to end?
	if (!edge_index)
		return(NULL);
	tmp = NULL;
	len = 0;
	head = ft_memalloc(sizeof(t_path));
	if (!head)
		ft_printf("error");
	head->i = end_room;
	head->next = NULL;
	tmp = head;
	while (edge_index)
	{
		//leaking
		prev = visited[edge_index];
		head = ft_memalloc(sizeof(t_path));
//		if (!head)
//			ft_error(2);
		head->i = edge_index;
		head->next = tmp;
		tmp = head;
		edge_index = prev;
	//	ft_dprintf(fd, "- %d -", edge_index); //test
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

