/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:08:16 by eprusako          #+#    #+#             */
/*   Updated: 2021/05/24 15:50:01 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_data(t_graph *data, char **input)
{
	ft_free2d((void **)input);
	ft_free2d((void **)data->weight_m);
	free_adlist(data->adlist, data->room_total * 2 + 1);
	ft_memdel((void **)&data);
}

/*
** Return 2d array for the weight values of edges between the rooms
*/

int	**create_matrix(int height, int width)
{
	int	**matrix;
	int	i;

	i = 0;
	matrix = ft_memalloc(sizeof(int *) * (height + 1));
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

t_path	*free_path(t_path *path)
{
	t_path	*tmp;

	while (path)
	{
		tmp = path;
		path = path->next;
		ft_memdel((void **)&tmp);
	}
	return (NULL);
}

t_path	**free_path_set(t_path ***set)
{
	int	i;

	i = 0;
	if (!set[0])
		return (NULL);
	while (set[0][i])
	{
		set[0][i] = free_path(set[0][i]);
		i++;
	}
	free(*set);
	return (NULL);
}

void	free_adlist(t_room **graph, size_t size)
{
	size_t	i;
	t_room	*tmp;

	if (!graph)
		return ;
	i = -1;
	while (++i < size && graph[i])
	{
		if (i < size / 2)
			ft_strdel(&graph[i]->name);
		while (graph[i])
		{
			tmp = graph[i];
			graph[i] = graph[i]->next;
			free(tmp);
		}
	}
	free(graph);
}
