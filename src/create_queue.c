/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/08 23:13:56 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_queue	*create_queue(int size, t_queue *new);

t_queue		*enqueue(int index, t_queue *q, t_room **adlist, int prev)
{
	t_room	*new;

//	I'm uncertain about the functionality of ft_memdup.
	new = ft_memdup(adlist[index], sizeof(t_room));
	// if (!new)
	// 	ft_error(2);
//	ft_printf("index %d new room index %d, adlist i index %d end? new %d old %d\n", index, new->index, adlist[index]->index, new->e, adlist[index]->e);
	new->prev_room_index = prev;
	new->index = index;
	new->next = NULL;
	if (!q->head)
		q->head = new;
	if (!q->tail)
		q->tail = new;
	else
	{
		q->tail->next = new;
		q->tail = new;
	}
	return (q);
}

t_queue		*dequeue(t_queue *q)
{
	t_room	*tmp;

	if (!q->head)
		return (NULL);
	tmp = q->head;
	q->head = q->head->next;
	ft_memdel((void**)&tmp);
	if (!q->head)
		q->tail = NULL;
	return (q);
}
