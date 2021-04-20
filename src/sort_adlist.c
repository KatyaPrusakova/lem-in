/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:04:07 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/20 12:58:28 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Splits the list from the middle into two lists. a and b are passed by
** reference in the parent function.
*/

void		partition_lst(t_room *head, t_room **a, t_room **b)
{
	t_room *slow;
	t_room *fast;

	if (!head || !head->next)
	{
		*a = head;
		*b = NULL;
		return;
	}
	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*b = slow->next;
	slow->next = NULL;
	*a = head;
}

t_room *merge_lists(t_room *a, t_room *b, int start, int **weight_matrix)
{
	t_room *head;
//	t_room	*print; //tst

	if (!a)
	{
//		ft_printf("a null\n");
		return (b);
	}
	else if (!b)
	{
//		ft_printf("b null\n");
		return (a);
	}
/*
	print = a;
	ft_printf("A: ");
	while (print)
	{
		ft_printf("%d -> ", print->index);
		print = print->next;
	}
	ft_n(1);
	print = b;
	ft_printf("B: ");
	while (print)
	{
		ft_printf("%d -> ", print->index);
		print = print->next;
	}
	ft_n(1);
*/

	if (weight_matrix[start][a->index] >= weight_matrix[start][b->index])
	{
		head = a;
		head->next = merge_lists(a->next, b, start, weight_matrix);
	}
	else
	{
		head = b;
		head->next = merge_lists(b->next, a, start, weight_matrix);
	}
/*
	print = head;
	ft_printf("merged list: ");
	while (print)
	{
		ft_printf("%d - ", print->index);
		print = print->next;
	}
	ft_n(2); */
	return (head);
}

/*
** Recursive merge funciton. Splits the list in two until it is split all the way
** into single nodes. Compares the two sides and arranges them in the list.
*/

t_room *adlist_mergesort(t_room *head, int start, int **weight_matrix)
{
	t_room	*a;
	t_room	*b;

/*
	t_room *print;


	print = head;
	while (print)
	{
		ft_printf("%d -- ", print->index);
		print = print->next;
	}
	ft_n(2);
*/
	if (!head || !head->next)
		return (head);
	partition_lst(head, &a, &b);
	a = adlist_mergesort(a, start, weight_matrix);
	b = adlist_mergesort(b, start, weight_matrix);
	head = merge_lists(a, b, start, weight_matrix);
	return (head);
}
