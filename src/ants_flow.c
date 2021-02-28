/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/28 10:22:35 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	create_rooms_in_path(t_path *path, t_graph *farm)
{
	t_room	*room;
	t_path	*prev;

	prev = path;
	path->prev = NULL;
	while (path)
	{
		room = farm->adlist[path->i];
		path->room = room;
		path = path->next;
	}
	prev->end = room;
	path = prev;
	path = path->next;
	while (path) //
	{
		path->prev = prev;
		prev = prev->next;
		path = path->next;
	}
}

int	paths_count(t_path **path, t_graph *graph)
{
	int		i;

	i = 0;
	while (path[i])
	{
		ft_printf("%d len %d\n: ", i, path[i]->len);
		create_rooms_in_path(path[i], graph);
		i++;
	}
	return (i);
}

void	push_ant_further(t_path *path)
{
	path = path->prev;
	while (path && path->room && !path->room->end)
	{
		if (path->room->antnbr > 0)
		{
			if (path->next->room->end)
			{
				path->next->room->antnbr++;
				//path->end->antnbr++;
				ft_printf("L%d-%s ", path->room->antnbr, path->next->room->name);
			}
			else
			{
				path->next->room->antnbr = path->room->antnbr;
				ft_printf("L%d-%s ", path->next->room->antnbr, path->next->room->name);
			}
			path->room->antnbr = 0;
		}
		path = path->prev;
	}
}

int	push_ant(t_path **path, int ant)
{
	t_path *temp;
	int	i;
	
	i = 0;
	while (path[i] && path[i]->ants_wait_list) // maybe ants_wait_list no need
	{
		temp = path[i];
	
		if (temp->next->room->end)
			temp->next->room->antnbr++;
		else
			temp->next->room->antnbr = ant;
		ft_printf("L%d-%s ", ant,
			temp->next->room->name);
		path[i]->ants_wait_list--;
		ant++;
		i++;
	}
	return (ant);
}

int		ants_left_in_path(t_path *path)
{
	t_path		*q_path;

	q_path = path->next;
	while (q_path)
	{
		if (q_path->room->antnbr > 0 && !q_path->room->end)
			return (1);
		q_path = q_path->next;
	}
	return (0);
}

void	push_ants_to_end(t_path **path)
{
	t_path *temp;
	int i;
//	int len;

	i = -1;
	while (path[++i])
	{
		if (ants_left_in_path(path[i]))
		{
			temp = path[i];
			while (temp->next->next)
			{
				temp = temp->next;
			}
			ft_printf("list %s prev %s\n",  temp->room->name, temp->prev->room->name);
			push_ant_further(temp);
		}
	//	path = path->next;
	}
}

/*
** IN TEORY, it is main loop functioon
** sends ants from start room while there is ants_wait_list in path
** using push_ant function
**
** if there are already ants in the path checked in function (ants_left_in_path)
** shall be moved to next room and printed out
**
** loop stops when all ants reached end rooom
**
*/

void	run_ants(t_path **path, t_graph *farm)
{
	int		i;
	int		total_ant;
	int		ant;
	t_path *temp;

	ant = 1;

	i = 0;
	total_ant = farm->ants; //delete
	while (ant <= farm->ants) // path[0]->end is pointer to end room (same for all paths)
	{
		i = 0;
		while (path[i])
		{
			//ft_printf("i %d\n", i);
			if (ants_left_in_path(path[i]))
			{
				temp = path[i];
				while (temp->next->next)
				{
					temp = temp->next;
				}
				//ft_printf("list %s prev %s\n",  temp->room->name, temp->prev->room->name);
				push_ant_further(temp);
			}
			if (ant <= farm->ants) //modify its segfault
			{
				ant = push_ant(path, ant);
			}
			i++;
		}
		ft_printf("\n");
	}
		push_ants_to_end(path);
}

int		*allocate_ants_to_rooms(t_path **path, t_graph *graph)
{
	int		i;
	int		j;
	int		ant_count;
	int		path_total;

	i = 0;
	j = -1;
	path_total = paths_count(path, graph);
	
	
	//  if not malloc, error
	ft_printf("sucsess %s %s\n", path[0]->room->name, path[1]->room->name);
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