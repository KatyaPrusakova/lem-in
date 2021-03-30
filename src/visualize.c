/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:19:16 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/30 16:35:47 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Prints the current state of queue to stdout.
*/

void	queue_to_visualizer(t_room **adlist, t_queue *q, int visualize)
{
	t_room	*tmp;

	if (!visualize)
		return;
	if (!adlist)
		ft_printf("unused variable");
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


void	visited_to_visualizer(int current_index, int visited_from, int visualize)
{
	if (!visualize)
		return;
	ft_printf("%d %d\n", current_index, visited_from);
}
