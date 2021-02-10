/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:19:34 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/10 17:36:30 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

/*
** Drawing the path finding algorithm before moving the ants.
*/

void	draw_algorithm(/*t_pointers *p, t_data *scl, t_room *rooms,*/ char **input)
{
	int i;

	i = move_index(input);
	while(ft_strcmp(input[i], "START_ANT_MOVEMENT"))
	{
		if (!ft_strchr(input[i], '-'))
		{
			ft_printf("Visited %s\n", input[i]);
		}
		else
		{
			ft_printf("rooms in queue %s\n", input[i]);
		}
		i++;
	}
	if (!ft_strcmp(input[i], "START_ANT_MOVEMENT"))
		ft_printf("path found\n");
}
