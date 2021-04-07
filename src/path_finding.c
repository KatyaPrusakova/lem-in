/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/07 12:40:43 by ksuomala         ###   ########.fr       */
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

	ft_printf("Search MOD\n");
	if (g->visualize)
		ft_printf("BFS\n");
	shortest = bfs(g, 1);
	if (!shortest)
		return (NULL);
	if (shortest->len >= g->ants)
		return (shortest);
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

t_path		**search_save(t_graph *g, t_path **set)
{
	ft_printf("Search 2nd\n");
	if (g->visualize)
		ft_printf("BFS\n");
	set[0] = bfs(g, 2);
	if (!set[0])
		return (NULL);
	else
		mod_edgeweight_path(g->weight_m, set[0], g, 1);
	set[1] = bfs(g, 2);
	if (!set[1])
	{
		free_path(set[0]);
		return (NULL);
	}
	else
		mod_edgeweight_path(g->weight_m, set[1], g, 1);
	return (set);
}

t_path		**path_to_array(t_path **array, t_path *p, int *i)
{
	array[*i] = p;
	*i += 1;
	return (array);
}

t_path		**compare_disjoint(t_graph *g, t_path **disjoint, t_path **shortest, t_path **final)
{
	int array_size;
	int disjoint_len;

	disjoint_len = set_rooms_total(disjoint);
	array_size = paths_in_array(final);
	if (disjoint_len && g->ants < disjoint_len)
	{
	//	ft_printf("Shortest is more efficient\n");
		final = path_to_array(final, *shortest, &array_size);
		mod_edgeweight_path(g->weight_m, *shortest, g, 1);
		disjoint[0] = free_path(disjoint[0]);
		disjoint[1] = free_path(disjoint[1]);
		free(disjoint);
	}
	else
	{
	//	ft_printf("Alternative set is more efficient\n");
		*shortest = free_path(*(shortest));
		final = path_to_array(final, disjoint[0], &array_size);
		mod_edgeweight_path(g->weight_m, disjoint[0], g, 1);
		final = path_to_array(final, disjoint[1], &array_size);
		mod_edgeweight_path(g->weight_m, disjoint[1], g, 1);
		free(disjoint);
	}
	return (final);
}

/*
** Finds the shortest path and two alternative paths. Compares them and chooses
** the most efficient set according to the number of ants. Keeps going until the
** (int)max_paths of paths is found.
*/
/*
t_path		**find_paths(t_graph *graph)
{
	t_path		**final_set;
	t_path		**disjoint_set;
	t_path		*shortest;
	int			paths_saved;

	paths_saved = 0;
	graph->max_paths = count_max_paths(graph);
	final_set = ft_memalloc(sizeof(t_path*) * graph->room_total);
	while (paths_saved < graph->max_paths)
	{
		shortest = search_modify(graph);
		if (!shortest)
			break ;
		if (shortest->len >= graph->ants || paths_saved + 1 == graph->max_paths)
		{
			final_set[paths_saved] = shortest;
			break ;
		}
		disjoint_set = ft_memalloc(sizeof(t_path*) * 3);
		disjoint_set = search_save(graph, disjoint_set);
		if (disjoint_set)
		{
			final_set = compare_disjoint(graph, disjoint_set, &shortest, final_set);
			paths_saved = paths_in_array(final_set);
		}
		else
		{
			final_set[paths_saved] = shortest;
			paths_saved++;
		}
	}
	return (final_set);
}
*/

t_path		**find_sets(t_graph *graph)
{
	t_path	**set_1;
	t_path	**set_2;
	int		i;

	graph->max_paths = count_max_paths(graph);
	set_1 = ft_memalloc(sizeof(t_path*) * graph->room_total);
	set_2 = ft_memalloc(sizeof(t_path*) * graph->room_total);
	if (graph->visualize)
		ft_printf("BFS\n");
	set_1 = bfs_set(graph, 1, set_1, graph->max_paths);
	if (set_rooms_total(set_1) >= graph->ants)
		return (set_1);
	if (graph->visualize)
		ft_printf("BFS\n");
	set_2 = bfs_set(graph, 1, set_2, graph->max_paths);
	while (set_2[0])
	{
		i = -1;
		while (set_2[++i])
			set_2[i] = free_path(set_2[i]);
		if (graph->visualize)
			ft_printf("BFS\n");
		set_2 = bfs_set(graph, 1, set_2, graph->max_paths);
	}
	if (graph->visualize)
		ft_printf("BFS\n");
	set_2 = bfs_set(graph, 2, set_2, graph->max_paths);
	return (set_2);
}
