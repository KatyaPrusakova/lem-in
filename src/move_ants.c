/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:01:22 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/15 19:06:59 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


/*
void	set_ant_queues(t_path **set, int ants)
{
	int i;

	while (ants)
	{
		i = 0;

	}
}
*/


void	move_all_to_end(int ant_amount, char *end_room)
{
	int i;

	i = 1;
	while (i <= ant_amount)
	{
		ft_printf("L%d-%s", i, end_room);
		i++;
		if (i <= ant_amount)
			write(1, " ", 1);
	}
	ft_n(1);
}

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
		if (room->ant && room->next)
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
*/

void		empty_paths(t_path **p)
{
	int	longest_path;
	int paths_left;
	int i;

	longest_path = 0;
	while (p[longest_path])
		longest_path++;
	paths_left = longest_path;
	longest_path--;

	while (paths_left)
	{
		i = longest_path;
		while (i >= 0)
		{
			if (p[i] && !push_path(p[i], 0))
			{
				p[i] = free_path(p[i]);
				paths_left--;
			}
			i--;
		}
		ft_n(1);
	}
}

int			pathlen_is_optimal(t_path **p, int path_nbr, int ants_left)
{
	int	pathset_capacity;
	int	flow_potential;

	pathset_capacity = set_rooms_total(p, path_nbr);
	flow_potential = p[path_nbr]->len * path_nbr;
	if (ants_left > flow_potential - pathset_capacity)
		return (1);
	else
	{
		ft_dprintf(fd, "pathno: %d pathlen = %d ants left = %d PATHSET:\n", path_nbr, flow_potential - pathset_capacity, ants_left);
		print_paths(p);
		return (0);
	}
}

void		move_ants(t_path **p, t_graph *g)
{
	int	ants_at_start;
	int	ant_no;
	int	i;

	//test
	ft_dprintf(fd, "PATHS:\nANTS: %d\n", g->ants);
	int x = 0;
	if (!p[x])
		ft_printf("PATH SET IS EMPTY\n");
	while (p[x])
	{
		ft_dprintf(fd, "%d\n", p[x]->len);
		x++;
	}
	//test
	ant_no = 1;
	ants_at_start = g->ants;
	while (ants_at_start)
	{
		i = 0;
		while (p[i])
		{
			if (!ants_at_start || !pathlen_is_optimal(p, i, ants_at_start))
			{
				if (!push_path(p[i], 0))
					p[i] = free_path(p[i]);
			}
			else
			{
				push_path(p[i], ant_no);
				ant_no++;
				ants_at_start--;
			}
			i++;
		}
		ft_n(1);
	}
	empty_paths(p);
}
