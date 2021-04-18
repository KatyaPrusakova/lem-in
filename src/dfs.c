/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:42:32 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/18 17:33:26 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			*init_visited(size_t len)
{
	int		*visited;
	size_t	i;

	visited = (int*)malloc(sizeof(int) * len);
	if (!visited)
		return (NULL);
	i = 0;
	visited[0] = 0;
	while (++i < len)
		visited[i] = -1;
	return (visited);
}

t_path		*dfs_find_path(t_graph *g, t_room *current, t_search s)
{
	t_path	*p;
	t_room	*tmp;
	int		prev;

	p = NULL;
	prev = current->index;
	if (!s.visited)
		s.visited = init_visited(g->room_total);
	if (current->index == s.start)
		current->prev_room_index = s.start;
	s.visited[current->index] = current->prev_room_index;
	if (g->visualize)
		ft_printf("%d %d\n", current->index, current->prev_room_index);
	tmp = current->next;
	while (tmp && !p)
	{
		if (tmp->index == s.end)
			p = save_path(s.visited, current->prev_room_index, g, s);
		else if (s.visited[tmp->index] == -1)
		{
			//freecurrent
			current = ft_memdup(g->adlist[tmp->index], sizeof(t_room));
			current->prev_room_index = prev;
			p = dfs_find_path(g, current, s);
		}
		tmp = tmp->next;
	}
	return (p);
}
