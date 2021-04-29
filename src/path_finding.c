/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/29 15:39:31 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			count_moves(t_path **path, int ants)
{
	int	path_count;
	int	lines;
	int ants_in_path;

	if (!path)
		return (0);
	lines = 0;
	path_count = paths_in_array(path);
	ants_in_path = 0;
	while (path_count && path[path_count - 1] && ants > 0)
	{
		if (path_count == 1 || pathlen_is_optimal(path, path_count - 1, ants))
		{
			ants -= path_count;
			if (path[path_count - 1]->len >= ants_in_path)
				ants_in_path = path[path_count - 1]->len;
			else
				ants_in_path--;
			lines++;
		}
		else
			path_count--;
	}
//	ft_dprintf(fd, "PATH LINES: %d\n", lines + ants_in_path);
	return (lines + ants_in_path);
}

/*
** Returns the set with more paths being used (larger flow). If the flow is
** equal,the lengh of the longest path in the set determines which path is used.
*/

t_path		**set_cmp(t_path **p1, t_path **p2, int ants)
{
	int	p1_lines;
	int p2_lines;

//	print_paths(p1);
//	ft_dprintf(fd, "\n\n");
//	print_paths(p2);
	p1_lines = count_moves(p1, ants);
	p2_lines = count_moves(p2, ants);
	if (!p2_lines || (p1_lines && p1_lines <= p2_lines))
	{
		p2 = free_path_set(&p2);
//		ft_dprintf(fd, "SET1\n");
		return (p1);
	}
	else
	{
		p1 = free_path_set(&p1);
//		ft_dprintf(fd, "SET2\n");
		return (p2);
	}
}

t_path		**clean_set(t_path **set, t_graph *g)
{
	int i;

	i = -1;
	while (set[++i])
		clean_path(set[i], g);
	return (set);
}

t_path		**sorted_search(t_graph *g)
{
	t_path *shortest;
	t_path **set;

	if (g->visualize)
		ft_printf("SEARCH\n");
	set = NULL;
	shortest = bfs(g, 0, g->room_total - 1);
	g->max_paths = count_max_paths(g);
	while (shortest)
	{
		mod_edgeweight_path(g, shortest);
		free_path(shortest);
		if (g->visualize)
			ft_printf("SEARCH\n");
		if (!set)
			set = clean_set(bfs_set(g, 0, g->room_total - 1), g);
		else
			set = set_cmp(set, clean_set(bfs_set(g, 0, g->room_total - 1), g), g->ants);
		if (g->visualize)
			ft_printf("SEARCH\n");
		shortest = bfs(g, 0, g->room_total - 1);
	}
	if (g->visualize)
		ft_printf("SEARCH\n");
//	set = bfs_set(g, 0, g->room_total - 1);
	// clean_set(set, g);
	return (set);
}

/*
** Returns a paths set with one path with a length of 0. This leads to
** all ants to be able to flow straight to the end room in one line.
*/

t_path		**unlimited_flow(void)
{
	t_path	**no_rooms;

	no_rooms = ft_memalloc(sizeof(t_path*) * 2);
	no_rooms[0] = ft_memalloc(sizeof(t_path));
	no_rooms[0]->len = 0;
	return (no_rooms);
}
