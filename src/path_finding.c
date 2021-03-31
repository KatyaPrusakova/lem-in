/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/31 15:56:51 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


/*
** Counts the maximum allowed paths (path bottleneck start/end).
*/

t_path		**find_paths(t_graph *graph)
{
	t_path		**paths;
	int			rooms_in_paths;
	int			max_paths;
	int			paths_saved;

	paths_saved = 0; //temporary variable
	max_paths = count_max_paths(graph);
	paths = ft_memalloc(sizeof(t_path*) * graph->room_total);
//	if (!paths)
//		ft_error(2);
	if (graph->visualize)
		ft_printf("BFS\n");
	while (paths_saved < max_paths)
	{
		ft_printf("PATHS FOUND %d, max %d\n", paths_saved, max_paths);
		paths[paths_saved] = bfs(max_paths, graph, 1);
		mod_edge_weight(graph->weight, paths[paths_saved]);
		rooms_in_paths = calculate_set_len(paths);
		//free path0
		if (rooms_in_paths >= graph->ants)
		{
			ft_printf("ants %d < rooms %d\n", graph->ants, rooms_in_paths);
			return (paths);
		}
		// free saved path
		print_matrix(graph->weight, graph->room_total);
		if (graph->visualize)
			ft_printf("BFS\n");
		free_path(paths[paths_saved]);
		paths[paths_saved] = bfs(max_paths, graph, 1);
		mod_edge_weight(graph->weight, paths[paths_saved]);
		free_path(paths[paths_saved]);
		print_matrix(graph->weight, graph->room_total);
		if (graph->visualize)
			ft_printf("BFS\n");
		// while < max_paths!!!
		paths[paths_saved] = bfs(max_paths, graph, 2);
		paths[paths_saved + 1] = bfs(max_paths, graph, 2);
		paths_saved = paths_in_array(paths);
		ft_printf("PATHS FND %d, mXX %d\n", paths_saved, max_paths);
	}

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

	return(paths);
}
