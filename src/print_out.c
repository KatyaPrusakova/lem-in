/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/24 00:30:09 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_rooms(t_graph* graph)
{
	int i;
	t_room	*tmp;

	i = 0;
	while (graph->adlist[i])
	{
		if (graph->adlist[i]->s || graph->adlist[i]->e)
			printf(" \n found |%s|\n", graph->adlist[i]->name);
		printf("%d |%s|", i, graph->adlist[i]->name);
		if (graph->adlist[i]->next != NULL)
		{
			tmp = graph->adlist[i];
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
				printf(" -> |%s|", tmp->name);
			}
		}
		printf("\n");
		
		i++;
	}
}
