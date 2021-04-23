/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:34:07 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/23 18:06:26 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		*delete_room_in_path(t_path *p, int index)
{
	t_path *tmp;
	t_path *delete;

	tmp = p;
	while (tmp->next)
	{
		if (tmp->next->i == index)
		{
			delete = tmp->next;
			tmp->next = tmp->next->next;
			ft_memdel((void**)&delete);
			return (p);
		}
		tmp = tmp->next;
	}
	return (p);
}

void		clean_path(t_path *p, t_graph *g)
{
	int	*len;
	int	set_len;

	len = &p->len;
	set_len = 0;
	while (p->next)
	{
		if (p->next->i >= g->room_total)
		{
			set_len++;
			delete_room_in_path(p, p->next->i);
		}
		p = p->next;
	}
	*len -= set_len;
}

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
	int prev_room_in_path = -1;
	if (g->visualize)
	{
		while (tmp)
		{
			if (tmp->i >= g->room_total && tmp->i - g->room_total != prev_room_in_path)
				ft_printf("%d |", tmp->i - g->room_total);
			else if (tmp->i != prev_room_in_path + g->room_total)
				ft_printf("%d |", tmp->i);
			prev_room_in_path = tmp->i;
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
