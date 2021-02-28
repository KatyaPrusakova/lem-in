/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/28 19:09:45 by eprusako         ###   ########.fr       */
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
	//	ft_printf("%d len %d\n: ", i, path[i]->len);
		create_rooms_in_path(path[i], graph);
		i++;
	}
	return (i);
}

t_path*		end_of_path(t_path *path)
{
	while (path->next)
		path = path->next;
	return (path);
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

void	push_ant(t_path *path, int ant)
{
	if (path->next->room->end)
		path->next->room->antnbr++;
	else
		path->next->room->antnbr = ant;
	ft_printf("L%d-%s ", ant,
		path->next->room->name);
	path->ants_wait_list--;
}

int		ants_left_in_path(t_path *q_path)
{
	while (q_path->next)
	{
		if (q_path->room->antnbr > 0 && !q_path->room->end)
			return (1);
		q_path = q_path->next;
	}
	return (0);
}

void	push_ants_to_end(t_path *path)
{
	path =  path->prev;
	while (path)
	{
		if (ants_left_in_path(path))
		{
			//ft_printf("list %s prev %s\n",  path->room->name, path->prev->room->name);
			push_ant_further(path);
		}
		path = path->next;
	}
}

/*
** it is main loop functioon
** sends ants from start room while there is ants_wait_list in path
** using push_ant function
**
** if there are already ants in the path checked in function (ants_left_in_path)
** shall be moved to next room and printed out
**
** loop stops when all ants reached end rooom
**
*/

void	run_ants_in_one_path(int ant, t_path *path)
{
	int i;

	i = 0;
	if (ants_left_in_path(path))
		{
			//ft_printf("list %s prev %s\n",  temp->room->name, temp->prev->room->name);
			push_ant_further(end_of_path(path));
		}
	if (path->ants_wait_list) //modify its segfault
	{
		push_ant(path, ant);
	}
}

void	last_push(t_path **path, t_graph *farm)
{
	int		i;
	int		antnbr;
	t_path *end;

	antnbr = 0;
	while (antnbr != farm->ants)
	{
		i = 0;
		while (path[i])
		{
			end = end_of_path(path[i]);
			antnbr = end->room->antnbr;
			if (ants_left_in_path(path[i]))
				push_ant_further(end);
			i++;
		}
		if (antnbr < farm->ants)
			ft_printf("\n");
	}
}

void	run_ants(int path_total, t_path **path, t_graph *farm)
{
	int		i;
	int		total_ant;
	int		ant;

	i = 0;
	ant = 1;
	total_ant = 0;
	while (total_ant <= farm->ants)
	{
		i = 0;
		while (path[i])
		{
			//ft_printf("i %d\n", i);
			run_ants_in_one_path(ant, path[i]);
			ant++;
			i++;
		}
		ft_printf("\n");
		total_ant += path_total;
	}
	last_push(path, farm);
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
//	ft_printf("sucsess %s %s\n", path[0]->room->name, path[1]->room->name);
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
	//print_paths(path);
	// j = -1;
	// while (++j < i)
	// {
	// 	ft_printf("path distributed %s %d|%d\n",  graph->adlist[path[j]->i]->name, path[j]->ants_wait_list, path[j]->len);
	// }
	//test
	run_ants(path_total, path, graph);
	return (NULL); //change
}