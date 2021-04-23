/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:19:16 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/23 15:05:25 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Prints the current state of queue to stdout.
		if (matrix[path->i][path->next->i] < 1)
*/

void	visualize_search(t_graph *g, t_room *room, t_queue *q, int **matrix)
{
	t_room	*tmp;
	int		index;
	int		prev_index;

	index = room->index;
	prev_index = room->prev_room_index;
	if (room->index >= g->room_total)
		index -= g->room_total;
	if (room->prev_room_index >= g->room_total)
		prev_index -= g->room_total;
	if (index != prev_index)
		ft_printf("E: %d %d w.%d\n", index, prev_index, matrix[room->prev_room_index][room->index]);
	else
		ft_printf("R: %d\n", index);
	tmp = q->head; // use var
	if (tmp && q)
		return ; //use var
/*	tmp = q->head;
	if (!q || !tmp)
		return;
	if (tmp)
		ft_printf("Q:");
	while (tmp)
	{
		if (tmp->index < g->room_total)
			ft_printf(" %d", tmp->index);
		tmp = tmp->next;
	}
	ft_n(1); */
}
