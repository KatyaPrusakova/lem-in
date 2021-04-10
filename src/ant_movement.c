/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:01:22 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/10 18:15:56 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		push_paths(t_path **p, t_room **room)
{
	t_path	*tmp;
	int		keep_antnbr;
	int		i;

	i = 0;
	while (p[i]->next)
	{
		tmp = p[i];
		keep_antnbr = p[i]->next;
		room[p[i]->i]
	}
}

void		move_ants(t_path **p, t_graph *g)
{
	int		unmoved_ants;

	unmoved_ants = g->ants;
	while (unmoved_ants)
	{
		move_ants_in_paths(p)
	}
}
