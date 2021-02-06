/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/06 11:57:22 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_queue	*create_queue(int size, t_queue *new);


// void			add_to_queue(t_queue *q, t_room	*room)
// {
// 	q->index = room->index;
// 	if (room->next) // && not in queue already
// 	{
// 		//
// 		while (room->next)
// 		{
// 			q = q->next;
// 			room = room->next;
// 			q->index = room->index;
// 		}
// 	}
//	printf("q->i %d\n", q->i);
//}

// void			print_queue(t_queue *q, int i)
// {
// 	while (q->next)
// 	{
// 		printf("queue note number %d q->index %d\n", i, q->index);
// 		q = q->next;
// 		i++;
// 	}
// }

// void			remove_from_queue(t_queue *q, int room_number)
// {
// 	q->index = q->index;
// 	room_number =  0;
// 	//remove link from linked list
// }

// int				queue_is_empty(t_queue *q)
// {
// 	if (q->next == NULL)
// 		return (1);
// 	return (0);
// }

// int				bfs(t_graph* data)
// {
// 	t_queue		*wait_list;
// 	int			i;
// 	t_room		*tmp;

// 	i = 0;
// //	wait_list = create_queue(data->room_total, data->q);
// 	print_queue(wait_list, 0);
// 	tmp = data->adlist[i];
// 	//tmp->visited = 1;

// 	// while didn't reach all nodes
// 		add_to_queue(wait_list, tmp);
// 	print_queue(wait_list, 0);

// 	// while (!queue_is_empty)
// 	// {
// 	// 	start_i = find_index_name_room(data, tmp->name);
// 	// 	printf("index of room %d\n", start_i);
// 	// 	add_to_queue(q, start_i);
// 	// 	tmp = tmp->next;
// 	// }
// 	return (1);
// }

// I think you don't need this function. Just use dequeue and enqueue.

// t_queue	*create_queue(int size, t_queue *new)
// {
// 	t_queue	*tmp;
// 	t_queue	*head;

// 	new = ft_memalloc(sizeof(t_queue));
// 	head = new;
// 	while (size--)
// 	{
// 		tmp = ft_memalloc(sizeof(t_queue));
// 		//new->index = 1;
// 		new->next = tmp;
// 		new = new->next;
// 	}
// //	printf("new->index %d\n", head->index);
// 	return (head);
// }

t_queue		*enqueue(int index, t_queue *q, t_room **adlist, int prev)
{
	t_room	*new;

//	I'm uncertain about the functionality of ft_memdup.
	new = ft_memdup(adlist[index], sizeof(t_room));
	// if (!new)
	// 	ft_error(2);
	ft_printf("index %d new room index %d, adlist i index %d end? new %d old %d\n", index, new->index, adlist[index]->index, new->e, adlist[index]->e);
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
	ft_memdel((void**)&tmp);
	if (q->tail == q->head)
		q->tail = NULL;
	q->head = q->head->next;
	return (q);
}
