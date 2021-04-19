/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:19:16 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/19 15:35:20 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Prints the current state of queue to stdout.
		if (matrix[path->i][path->next->i] < 1)
*/

void	visualize_search(t_room *room, t_queue *q, int **matrix)
{
	t_room	*tmp;

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
