/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:01:22 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/10 22:02:32 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Pushes all ants forward in all paths of the pathset **p. Adds add_ant to the
** first room. Returns the amount of ants found in the path.
*/

int			push_path(t_path *p, int add_ant)
{
	t_path *room;
	int		push_ant;
	int		prev_ant;
	int		ants_in_path;

	ants_in_path = 0;
	prev_ant = add_ant;
	room = p->next;
	while (room)
	{
		if (room->ant)
			ants_in_path++;
		if (prev_ant)
			ft_printf("L%d-%s ", prev_ant, room->name);
		if (prev_ant && !room->next)
			ants_in_path--;
		push_ant = room->ant;
		room->ant = prev_ant;
		prev_ant = push_ant;
		room = room->next;
	}
	return (ants_in_path);
}

/*
** The remaining paths that still have ants are pushed empty. The path set
** is looped reversly, because the first ones in the set are the shortest and will
** be empty first.
*/

void		empty_paths(t_path **p)
{
	int	paths_left;
	int i;

//	ft_printf("empty paths\n");
	paths_left = 0;
	while (p[paths_left])
		paths_left++;
	paths_left--;
//	ft_printf("paths left %d\n", paths_left);
	while (p[paths_left])
	{
		i = paths_left;
		while (i && p[i])
		{
			if (!push_path(p[i], 0))
				p[i] = free_path(p[i]);
			i--;
		}
		if (p[paths_left])
			ft_n(1);
	}
}

void		move_ants(t_path **p, t_graph *g)
{
	int	ants_at_start;
	int	ant_no;
	int	i;

	ant_no = 1;
	ants_at_start = g->ants;
	while (ant_no <= g->ants)
	{
		i = 0;
		while (p[i] && ants_at_start)
		{
			if (i && p[i]->len > p[i - 1]->len + ants_at_start)
			{
				p[i] = free_path(p[i]);
				break;
			}
			push_path(p[i], ant_no);
			i++;
			ant_no++;
			ants_at_start--;
		}
		ft_n(1);
	}
	empty_paths(p);
}
