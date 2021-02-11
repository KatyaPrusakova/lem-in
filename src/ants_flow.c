/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/10 12:12:51 by eprusako         ###   ########.fr       */
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
** ant_count moove too next room
** If path lenght plus number of ants in room less or equal then
** add ants to current room
*/

int		*allocate_ants_to_rooms(t_path **path, t_graph *graph)
{
	int		i;
	int		j;
	int		ant_count;
	int		*ants_in_roooms;

	i = 0;
	j = 0;
	ants_in_roooms = ft_memalloc(sizeof(int) * paths_count(path));
	//  if not malloc, error
	
	ant_count = 1;
	ants_in_roooms[0] = 1;
	while (ant_count <= graph->ants)
	{
		j = 0;
		while (path[j]->len + ants_in_roooms[j] > ant_count)
			j++;
		ant_count++;
		ants_in_roooms[j] += 1;
	}
	j = 0;
	while (ants_in_roooms[j])
	{
		ft_printf("number oof ants in room %d|%d\n", ants_in_roooms[j]);
		j++;
	}
	return (ants_in_roooms);
}