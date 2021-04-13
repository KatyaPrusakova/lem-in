/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:01:22 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/13 15:54:01 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
** The remaining paths that still have ants are pushed empty. The path set
** is looped reversly, because the first ones in the set are the shortest and will
** be empty first.
*/

void		empty_paths(t_path **p)
{
	int	longest_path;
	int i;

//	ft_printf("empty paths\n");
	longest_path = 0;
	while (p[longest_path])
		longest_path++;
	longest_path--;
//	ft_printf("paths left %d\n", longest_path);
	while (p[longest_path])
	{
		i = longest_path;
		while (i >= 0 && p[i])
		{
			if (!push_path(p[i], 0))
				p[i] = free_path(p[i]);
			i--;
		}
	//	if (p[longest_path])
			ft_n(1);
	}
}

void		move_ants(t_path **p, t_graph *g)
{
	int	ants_at_start;
	int	max_path_len;
	int	ant_no;
	int	i;


	//test
	ft_dprintf(fd, "PATHS:\n");
	int x = 0;
	while (p[x])
	{
		ft_dprintf(fd, "%d\n", p[x]->len);
		x++;
	}
	//test
	ant_no = 1;
	ants_at_start = g->ants;
	max_path_len = 0;
	while (ant_no <= g->ants)
	{
		i = 0;
		while (p[i] && ants_at_start)
		{
			if (i && p[i]->len > max_path_len)
			{
				if (!push_path(p[i], 0))
					p[i] = free_path(p[i]);
			}
			else
			{
				push_path(p[i], ant_no);
				ant_no++;
				ants_at_start--;
				max_path_len = p[0]->len + ants_at_start;
			}
			i++;
		}
		ft_n(1);
	}
	empty_paths(p);
}
