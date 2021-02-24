/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/24 22:07:56 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	paths_count(t_path **path)
{
	int		i;

	i = 0;
	while (path[i])
		i++;
	ft_printf("total len of all paths: %d\n: ", i);
	return (i);
}


/*
** If path lenght plus number of ants in room more then 
** ant_count move to next room
** If path lenght plus number of ants in room less or equal then
** add ants to current room
*/

static void		move_ants(t_path *path, t_graph *graph)
{
	t_path *temp;
	temp = path->next;
	
	ft_printf("L%d-%s ", path->ant_id, graph->adlist[temp->i]->name);
	//put ant to next room in linked list
	temp = path->next->next;
	temp->ant_id = path->ant_id;
	temp->occupied = 1;
	ft_printf("\n occupied L%d-%s \n", path->ant_id, graph->adlist[temp->i]->name);
}

// static void		next_room_busy(t_path *path, t_graph *graph)
// {
// 	int id;
// 	path = path->next;
// 	while (path->next)
// 	{
// 		path = path->next;
// 	}
// 	id = path->ant_id;
// 	path = path->next;
// 	path->ant_id = id;
// 	path->occupied = 1;
// 	ft_printf(" next room L%d-%s ", path->ant_id, graph->adlist[path->i]->name);
// }

int		*allocate_ants_to_rooms(t_path **path, t_graph *graph)
{
	int		i;
	int		j;
	int		ant_count;
	int		path_total;
	int		*ants_in_paths;

	i = 0;
	j = -1;
	path_total = paths_count(path);
	ants_in_paths = ft_memalloc(sizeof(int) * path_total);
	//  if not malloc, error
	ft_printf("path_total %d\n",path_total );
	ant_count = graph->ants;

	while (ant_count > 0)
	{
		i = 0;
		ft_printf("loop %d\n", ant_count );
		while (ant_count < path[i]->len && path_total > 1)
		{
			path_total--;
		}
		ft_printf("loop path_total %d\n", path_total );
		while (i < path_total)
			ants_in_paths[i++]++;
		ant_count -= path_total;
	}

	j = -1;
	while (path[++j])
	{
		path[j]->ants_wait_list = ants_in_paths[j];
	}

	//test
	print_paths(path);
	j = -1;
	while (++j < i)
	{
		ft_printf("path distributed %d|%d\n", path[j]->ants_wait_list, path[j]->len);
	}
	//test
	//t_path *tmp;
	j = 0;
	ant_count = graph->ants;
	i = 1;
	while (ant_count)
	{
		j = 0;
		while (path[j])
		{
			if (path[j]->ants_wait_list) // while there are ants awaiting
			{
				path[j]->ant_id = i;
				move_ants(path[j], graph);
				path[j]->ants_wait_list--; //sending one to path
				i++;
			}
			j++;
		}
		ant_count--;
	}
	
	return (ants_in_paths); //change
}
