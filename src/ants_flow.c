/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/17 17:32:20 by eprusako         ###   ########.fr       */
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


/*
** If path lenght plus number of ants in room more then 
** ant_count move to next room
** If path lenght plus number of ants in room less or equal then
** add ants to current room
*/

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
		//ft_printf("loop %d\n", ant_count );
		while (ant_count < path[i]->len && path_total > 1)
		{
			path_total--;
		}
		//ft_printf("loop path_total %d\n", path_total );
		while (i < path_total)
			ants_in_paths[i++]++;
		ant_count -= path_total;
	}
	//test
	while (++j < i)
	{
		ft_printf("number of ants in room %d|%d\n", ants_in_paths[j], j);
	}
	//test
	
	return (ants_in_paths);
}