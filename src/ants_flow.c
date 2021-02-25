/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/25 15:27:26 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	paths_count(t_path **path)
{
	int		i;

	i = 0;
	while (path[i])
		i++;
	//ft_printf("total len of all paths: %d\n: ", i);
	return (i);
}


void	push_ant_further(t_path *list)
{
	list = list->prev;
	while (list && list->room && !list->room->end)
	{
		if (list->room->antnbr > 0)
		{
			if (list->next->room->end)
			{
				list->next->room->antnbr++;
				ft_printf("L%d-%s ", list->room->antnbr,
					list->next->room->name);
			}
			else
			{
				list->next->room->antnbr = list->room->antnbr;
				ft_printf("L%d-%s ", list->next->room->antnbr,
					list->next->room->name);
			}
			list->room->antnbr = 0;
		}
		list = list->prev;
	}
}

void	push_ant(t_path *list, int ant)
{
	if (list->next->room->end)
		list->next->room->antnbr++;
	else
		list->next->room->antnbr = ant;
	ft_printf("L%d-%s ", ant,
		list->next->room->name);
}

int		ants_left_in_path(t_path *path)
{
	t_path		*q_path;

	q_path = path->next;
	while (q_path)
	{
		if (q_path->room->antnbr > 0 && q_path->room->end)
			return (1);
		q_path = q_path->next;
	}
	return (0);
}

void	push_ants_to_end(t_path *path, int size)
{
	while (size < path->size)
	{
		if (ants_left_in_path(path[size]))
			push_ant_further(path[size].endlist);
		size++;
	}
}



void	run_ants(t_path **path, t_graph *farm)
{
	int		i;
	int		size;
	int		ant;
	t_path *temp;

	ant = 1;
	// temp = path[0];
	// temp[i]
	size = paths_count(path);
	while (ant != farm->ants) //corr
	{
		while (i < size)
		{
			ft_printf("size %d %d\n", path[i]);
			if (ants_left_in_path(path[i]))
				push_ant_further(path[i].endlist);
			if (path[i]->ants_wait_list > 0)
			{
				push_ant(path[i], ant);
				path[i]->ants_wait_list--;
			}
			i++;
			ant++;
		}
		push_ants_to_end(path, size);
		ft_printf("\n");
	}
}

int		*allocate_ants_to_rooms(t_path **path, t_graph *graph)
{
	int		i;
	int		j;
	int		ant_count;
	int		path_total;

	i = 0;
	j = -1;
	path_total = paths_count(path);
	//  if not malloc, error
//	ft_printf("path_total %d\n",path_total );
	ant_count = graph->ants;

	while (ant_count > 0)
	{
		i = 0;
		//ft_printf("loop %d\n", ant_count );
		while (ant_count < path[i]->len && path_total > 1)
		{
			path_total--;
		}
		//ft_printf("loop path_total %d\n", path_total );
		while (i < path_total)
			path[i++]->ants_wait_list++;
		ant_count -= path_total;
	}
	//test
	print_paths(path);
	j = -1;
	while (++j < i)
	{
		ft_printf("path distributed %s %d|%d\n",  graph->adlist[path[j]->i]->name, path[j]->ants_wait_list, path[j]->len);
	}
	//test
	
	run_ants(path, graph);
	
	return (NULL); //change
}