/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/05 12:45:38 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_queue	*create_queue(int size, t_queue *new);


void			add_to_queue(t_queue *q, t_room	*room)
{
	q->index = room->index;
	if (room->next) // && not in queue already
	{
		//
		while (room->next)
		{
			q = q->next;
			room = room->next;
			q->index = room->index;
		}
	}
//	printf("q->i %d\n", q->i);
}

void			print_queue(t_queue *q, int i)
{
	while (q->next)
	{
		printf("queue note number %d q->index %d\n", i, q->index);
		q = q->next;
		i++;
	}
}

void			remove_from_queue(t_queue *q, int room_number)
{
	q->index = q->index;
	room_number =  0;
	//remove link from linked list
}

int				queue_is_empty(t_queue *q)
{
	if (q->next == NULL)
		return (1);
	return (0);
}

int				bfs(t_graph* data, int start_i)
{
	t_queue		*q;
	t_room		*tmp;

	q = create_queue(data->room_total, data->q);
	print_queue(q, 0);
	tmp = data->adlist[start_i];
	//tmp->visited = 1;
	
	// while didn't reach all nodes
		add_to_queue(q, tmp);
	print_queue(q, 0);
	
	// while (!queue_is_empty)
	// {
	// 	start_i = find_index_name_room(data, tmp->name);
	// 	printf("index of room %d\n", start_i);
	// 	add_to_queue(q, start_i);
	// 	tmp = tmp->next;
	// }
	return (1);
}

t_queue	*create_queue(int size, t_queue *new)
{
	t_queue	*tmp;
	t_queue	*head;

	new = ft_memalloc(sizeof(t_queue));
	head = new;
	while (size--)
	{
		tmp = ft_memalloc(sizeof(t_queue));
		//new->index = 1;
		new->next = tmp;
		new = new->next;
	}
//	printf("new->index %d\n", head->index);
	return (head);
}
