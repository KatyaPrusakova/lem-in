/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:08:16 by eprusako          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/02/21 23:10:32 by ksuomala         ###   ########.fr       */
=======
/*   Updated: 2021/02/24 11:24:03 by eprusako         ###   ########.fr       */
>>>>>>> 7b8650c93ffa1333bd20c873257ebbd74f8fad29
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Return 2d array for the weight values of edges between the rooms
*/

int **create_matrix(int height, int width)
{
	int	**matrix;
	int	i;

	i = 0;
	matrix = ft_memalloc(sizeof(int*) * height);
	if (!matrix)
		ft_printf("malloc failed");
	while (i < width)
	{
		matrix[i] = ft_memalloc(sizeof(int) * width);
		if (!matrix[i])
			ft_printf("malloc failed!");
		i++;
	}
	return (matrix);
}


t_graph*		create_graph(int rooms)
{
	t_graph		*new;

	new = ft_memalloc(sizeof(t_graph));
	new->adlist = ft_memalloc(sizeof(t_room*) * (rooms+1));
	new->room_total = rooms;
	new->weight = create_matrix(rooms, rooms);
	return (new);
}

void			adlist_free(t_room **graph, size_t size)
{
	size_t		i;
	t_room		*tmp;

	if (!graph)
		return ;
	i = -1;
	while (++i < size)
	{
		while (graph[i])
		{
			tmp = graph[i];
			graph[i] = graph[i]->next;
			free(tmp);
		}
	}
	free(graph);
}
