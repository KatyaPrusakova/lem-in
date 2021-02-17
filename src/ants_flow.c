/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/17 13:53:30 by eprusako         ###   ########.fr       */
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

int		*allocate_ants_to_rooms(t_path **path, t_graph *graph)
{
	int		i;
	int		j;
	int		ant_count;
	int		path_total;
	int		*ants_in_paths;

	i = 0;
	j = 0;
	path_total = paths_count(path);
	ants_in_paths = ft_memalloc(sizeof(int) * path_total);
	//  if not malloc, error
	ft_printf("path_total %d\n",path_total );
	ant_count = 1;
	ants_in_paths[0] = 1;
	while (ant_count < graph->ants)
	{
		i = 0;
		while (i < path_total)
			ants_in_paths[i++]++;
		graph->ants -= path_total;
	}
	ft_printf("number oof ants in room %d|%d\n", ants_in_paths[j], j);
	return (ants_in_paths);
}