/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/01 16:52:58 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Search modify finds the shortest path on the first search. The shortest path
** edge weights are modified, and the edges along the shortest path are only
** used reversly on the second search. The second search is only used to modify
** the edge values for the next search in search_save. search_modify
** returns the first shortest path found in the graph.
*/

t_path		*search_modify(t_graph *g)
{
	t_path *shortest;
	t_path *find_bottleneck;

	if (g->visualize)
		ft_printf("BFS\n");
	shortest = bfs(g, 1);
	mod_edgeweight_path(g->weight_m, shortest, g, 0);
	print_matrix(g->weight_m, g->room_total); //test
	if (g->visualize)
		ft_printf("BFS\n");
	find_bottleneck = bfs(g, 1);
	mod_edgeweight_path(g->weight_m, find_bottleneck, g, 0);
	print_matrix(g->weight_m, g->room_total); //test
	find_bottleneck = free_path(find_bottleneck);
	return (shortest);
}

t_path		**search_save(t_graph *g, t_path **set, int *paths_saved)
{
	if (g->visualize)
		ft_printf("BFS\n");
	print_rooms(g); //test
	set[*paths_saved] = bfs(g, 2);
	print_matrix(g->weight_m, g->room_total); //test
	if (set[*paths_saved])
	{
		mod_edgeweight_path(g->weight_m, set[*paths_saved], g, 1);
		*paths_saved += 1;
	}
	print_rooms(g); //test
	print_matrix(g->weight_m, g->room_total); //test
	set[*paths_saved] = bfs(g, 2);
	if (set[*paths_saved])
	{
		mod_edgeweight_path(g->weight_m, set[*paths_saved], g, 1);
		*paths_saved += 1;
	}
	return (set);
}

/*
** Counts the maximum allowed paths (path bottleneck start/end).
*/

t_path		**find_paths(t_graph *graph)
{
	t_path		**paths;
	t_path		*shortest;
	int			paths_saved;

	paths_saved = 0;
	graph->max_paths = count_max_paths(graph);
	paths = ft_memalloc(sizeof(t_path*) * graph->room_total);
	shortest = search_modify(graph);
	ft_printf("Shortest path found\n"); //test
	if (shortest->len >= graph->ants)
	{
		paths[0] = shortest;
		return (paths);
	}
	paths = search_save(graph, paths, &paths_saved);
	return (paths);
}
