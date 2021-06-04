/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:34:07 by ksuomala          #+#    #+#             */
/*   Updated: 2021/06/04 17:10:44 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	*delete_room_in_path(t_path *p, int index)
{
	t_path	*tmp;
	t_path	*delete;

	tmp = p;
	while (tmp->next)
	{
		if (tmp->next->i == index)
		{
			delete = tmp->next;
			tmp->next = tmp->next->next;
			ft_memdel((void **)&delete);
			return (p);
		}
		tmp = tmp->next;
	}
	return (p);
}

void	clean_path(t_path *p, t_graph *g)
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

t_path	*add_room_to_path(t_path *head, char *name, int index)
{
	t_path	*tmp;

	tmp = head;
	head = ft_memalloc(sizeof(t_path));
	if (!head)
	{
		free_path(tmp);
		print_error(2, NULL);
	}
	head->i = index;
	head->name = name;
	head->next = tmp;
	return (head);
}

t_path	*save_path(int *visited, t_graph *g, t_search s, int prev_room)
{
	t_path	*head;
	int		len;

	head = NULL;
	head = add_room_to_path(head, g->adlist[s.end]->name, s.end);
	len = 0;
	while (prev_room != s.start)
	{
		if (prev_room == -2)
			return (NULL);
		head = add_room_to_path(head, g->adlist[prev_room]->name, prev_room);
		prev_room = visited[prev_room];
		len++;
	}
	head = add_room_to_path(head, g->adlist[s.start]->name, s.start);
	head->len = len;
	return (head);
}

/*
** Check if any of the rooms in the found path are already used on a saved
** path. If not, save the path, and return the paths array. Otherwise return
** path array unmodified.
*/

int	check_path(t_graph *graph, t_search s, int *path_no, int prev_room)
{
	t_path	*found_path;

	found_path = save_path(s.visited, graph, s, prev_room);
	if (graph->visualize)
		path_to_visualizer(found_path, graph->room_total, 0);
	if (!found_path)
		return (1);
	s.set[*path_no] = found_path;
	*path_no += 1;
	return (1);
}
