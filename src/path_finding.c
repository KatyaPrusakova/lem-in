/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/01 14:18:54 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path		**search_modify(t_graph *g, t_path **set, int *paths_saved)
{
	if (g->visualize)
		ft_printf("BFS\n");
	set[*paths_saved] = bfs(g->max_paths, g, 1);
	if (set_rooms_total(set) >= g->ants)
		return (set);
	mod_edgeweight_path(g->weight_m, set[*paths_saved], g, 0);
	print_matrix(g->weight_m, g->room_total); //test
	if (g->visualize)
		ft_printf("BFS\n");
	set[*paths_saved] = free_path(set[*paths_saved]);
	set[*paths_saved] = bfs(g->max_paths, g, 1);
	mod_edgeweight_path(g->weight_m, set[*paths_saved], g, 0);
	print_matrix(g->weight_m, g->room_total); //test
	set[*paths_saved] = free_path(set[*paths_saved]);
	return (set);
}

t_path		**search_save(t_graph *g, t_path **set, int *paths_saved)
{
	if (g->visualize)
		ft_printf("BFS\n");
	set[*paths_saved] = bfs(g->max_paths, g, 2);
	if (set[*paths_saved])
	{
		mod_edgeweight_path(g->weight_m, set[*paths_saved], g, 1);
		*paths_saved += 1;
	}
	set[*paths_saved] = bfs(g->max_paths, g, 2);
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
	int			paths_saved;

	paths_saved = 0;
	graph->max_paths = count_max_paths(graph);
	paths = ft_memalloc(sizeof(t_path*) * graph->room_total);
	search_modify(graph, paths, &paths_saved);
	if (paths[0])
		return (paths);
	paths = search_save(graph, paths, &paths_saved);
	return (paths);
}
//	if (!paths)
//		ft_error(2);
	// if (graph->visualize)
		// ft_printf("BFS\n");
	// while (paths_saved < max_paths)
	// {
	// 	ft_printf("PATHS FOUND %d, max %d\n", paths_saved, max_paths);
	// 	paths[paths_saved] = bfs(max_paths, graph, 1);
	// 	mod_edgeweight_path(graph->weight_m, paths[paths_saved], graph, 0);
	// 	rooms_in_paths = set_rooms_total(paths);
	// 	if (rooms_in_paths >= graph->ants || paths_saved + 1 == max_paths)
	// 		return (paths);
	// 	print_matrix(graph->weight_m, graph->room_total);
	// 	if (graph->visualize)
	// 		ft_printf("BFS\n");
	// 	free_path(paths[paths_saved]);
	// 	paths[paths_saved] = bfs(max_paths, graph, 1);
	// 	mod_edgeweight_path(graph->weight_m, paths[paths_saved], graph, 0);
	// 	free_path(paths[paths_saved]);
	// 	print_matrix(graph->weight_m, graph->room_total);
	// 	if (graph->visualize)
	// 		ft_printf("BFS\n");
	// 	// while < max_paths!!!
	// 	paths[paths_saved] = bfs(max_paths, graph, 2);
	// 	mod_edgeweight_path(graph->weight_m, paths[paths_saved], graph,1);
	// 	paths[paths_saved + 1] = bfs(max_paths, graph, 2);
	// 	mod_edgeweight_path(graph->weight_m, paths[paths_saved + 1], graph, 1);
	// 	paths_saved = paths_in_array(paths);
	// 	ft_printf("PATHS FND %d, mXX %d\n", paths_saved, max_paths);

	//print_paths(paths);
// remove the shortest paths links from the graph;
/*	if (paths[0] && paths[0]->len > 1)
	{
		ft_dprintf(fd, "\nBFS 2.0\n");

		reverse_path(paths[0], graph);
		paths = bfs(max_paths, graph, graph->adlist[0], graph->visualize);
		print_rooms(graph);
	} */
//	print_paths(paths);

