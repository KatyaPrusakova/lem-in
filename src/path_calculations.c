/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_calculations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:54:23 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/25 14:47:52 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Counts the maximum amount of needed paths. Maximum path count is the
** min amount of rooms linked to start or end rooms.
*/

int		count_max_paths(t_graph *graph)
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

int		paths_in_array(t_path **set)
{
	int i;

	i = 0;
	while (set[i])
		i++;
	return (i);
}

int		set_rooms_total(t_path **set, int last_path)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (set[i] && i <= last_path)
	{
		count += set[i]->len;
		i++;
	}
	return (count);
}

int		path_cmp(t_path *p1, t_path *p2)
{
	while (p1 && p2)
	{
		if (p1->i != p2->i)
			return (1);
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p1 || p2)
		return (1);
	else
		return (0);
}
