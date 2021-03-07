/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_calculations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:54:23 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/02 17:36:01 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

int		calculate_set_lenght(t_path **set)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (set[i])
	{
		count += set[i]->len;
		i++;
	}
	return (count);
}
