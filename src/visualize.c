/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:19:16 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/22 17:18:13 by ksuomala         ###   ########.fr       */
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
	ft_printf("%d %d w.%d\n", room->index, room->prev_room_index, matrix[room->prev_room_index][room->index]);
	tmp = q->head;
	if (!q || !tmp)
		return;
	while (tmp)
	{
		ft_printf("%d-%d ", tmp->prev_room_index, tmp->index);
		tmp = tmp->next;
	}
	ft_n(1);
}
