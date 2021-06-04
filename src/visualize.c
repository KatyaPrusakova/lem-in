/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:19:16 by ksuomala          #+#    #+#             */
/*   Updated: 2021/06/04 17:09:54 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	visualizer_clean_graph(int visualize)
{
	if (visualize)
		ft_printf("SEARCH\n");
}

void	path_to_visualizer(t_path *p, int offset, int mod_flow)
{
	int	prev_room;

	prev_room = -1;
	if (mod_flow)
	{
		ft_printf("%dMOD|", p->i);
		p = p->next;
	}
	while (p)
	{
		if (p->i >= offset && p->i - offset != prev_room)
			ft_printf("%d |", p->i - offset);
		else if (p->i != prev_room + offset)
			ft_printf("%d |", p->i);
		prev_room = p->i;
		p = p->next;
	}
	ft_n(1);
}

void	visualize_search(t_graph *g, t_room *room, int **matrix)
{
	int		index;
	int		prev_index;

	index = room->index;
	prev_index = room->prev_room_index;
	if (room->index >= g->room_total)
		index -= g->room_total;
	if (room->prev_room_index >= g->room_total)
		prev_index -= g->room_total;
	if (index != prev_index)
	{
		ft_printf("E: %d %d w.%d\n", index, prev_index,
			matrix[room->prev_room_index][room->index]);
	}
	else
		ft_printf("R: %d\n", index);
}
