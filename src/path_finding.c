/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/22 20:10:29 by ksuomala         ###   ########.fr       */
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

/*

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
	mod_edgeweight_path(g, shortest, g, 0);
	print_matrix(g->weight_m, g->room_total); //test
	if (g->visualize)
		ft_printf("BFS\n");
	find_bottleneck = bfs(g, 1);
	mod_edgeweight_path(g, find_bottleneck, g, 0);
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
		mod_edgeweight_path(g, set[0], g, 1);
	set[1] = bfs(g, 2);
	if (!set[1])
	{
		free_path(set[0]);
		return (NULL);
	}
	else
		mod_edgeweight_path(g, set[1], g, 1);
	return (set);
}

t_path		**path_to_array(t_path **array, t_path *p, int *i)
{
	array[*i] = p;
	*i += 1;
	return (array);
}
*/

/*

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
		mod_edgeweight_path(g, *shortest, g, 1);
		disjoint[0] = free_path(disjoint[0]);
		disjoint[1] = free_path(disjoint[1]);
		free(disjoint);
	}
	else
	{
	//	ft_printf("Alternative set is more efficient\n");
		*shortest = free_path(*(shortest));
		final = path_to_array(final, disjoint[0], &array_size);
		mod_edgeweight_path(g, disjoint[0], g, 1);
		final = path_to_array(final, disjoint[1], &array_size);
		mod_edgeweight_path(g, disjoint[1], g, 1);
		free(disjoint);
	}
	return (final);
}

*/

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
	ft_dprintf(fd, "PATH LINES: %d\n", lines + ants_in_path);
	return (lines + ants_in_path);
}

/*
** Returns the set with more paths being used (larger flow). If the flow is equal,
** the lengh of the longest path in the set determines which path is used.
*/

t_path		**set_cmp(t_path **p1, t_path **p2, int ants)
{
	int	p1_lines;
	int p2_lines;

	print_paths(p1);
	ft_dprintf(fd, "\n\n");
	print_paths(p2);
	p1_lines = count_moves(p1, ants);
	p2_lines = count_moves(p2, ants);
	if (!p2_lines || (p1_lines && p1_lines <= p2_lines))
	{
		p2 = free_path_set(&p2);
		ft_dprintf(fd, "SET1\n");
		return (p1);
	}
	else
	{
		p1 = free_path_set(&p1);
		ft_dprintf(fd, "SET2\n");
		return (p2);
	}
}


/*
t_path		**find_sets(t_graph *graph)
{
	t_path	**set_1;
	t_path	**set_2;
//	t_path	*dfs;
	t_search s;
//	t_path	**reverse;

	ft_bzero(&s, sizeof(t_search));
	s.start = 0;
	s.end = graph->room_total - 1;
	graph->max_paths = count_max_paths(graph);
//	set_1 = ft_memalloc(sizeof(t_path*) * graph->room_total);
//	set_2 = ft_memalloc(sizeof(t_path*) * graph->room_total);
	set_1 = bfs_set(graph, 1, 0, graph->room_total - 1);
	ft_dprintf(fd, "First set\n");
	if (graph->visualize)
		ft_printf("BFS\n");
//	dfs = dfs_find_path(graph, graph->adlist[0], s);
	//set_1[8] = dfs;
//	print_paths(&dfs);
//	print_paths(set_1);
	set_2 = NULL;
//	set_2 = bfs_set_weightend(graph, 1, 0, graph->room_total - 1);
	set_2 = dfs_mod_all(graph, graph->adlist[0], &s, NULL);
	print_matrix(graph->weight_m, graph->room_total);
	mod_edgeweight_set(graph, set_2);
	print_matrix(graph->weight_m, graph->room_total);
//	bfs_set_modify(graph, 1, 0, graph->room_total);
//	ft_dprintf(fd, "Second set\n");
//	print_paths(set_2);
//	ft_dprintf(fd, "Compare sets\n");
//	set_1 = set_cmp(set_1, set_2, graph->ants);
//	ft_dprintf(fd, "compared set\n");
	//set_2 = bfs_set(graph, 2, 0, graph->room_total);
	//set_1 = set_cmp(set_1, set_2, graph->ants);
//	print_paths(set_1);
	//while ((bfs_set_modify(graph, 1, 0, graph->room_total - 1)))
	//{
	//bfs_set_modify(graph, 1, 0, graph->room_total - 1);
	//		print_paths(set_2);
	//	set_1 = set_cmp(set_1, set_2, graph->ants);
	//	set_2 = bfs_set(graph, 2, 0, graph->room_total);
	//	set_1 = set_cmp(set_1, set_2, graph->ants);
	//}
	set_2 = bfs_set(graph, 2, 0, graph->room_total - 1);
//	set_1 = set_cmp(set_1, set_2, graph->ants);
//	reverse = bfs_set(graph, 4, graph->room_total - 1, 0);
	set_1 = set_cmp(set_1, set_2, graph->ants);
	ft_dprintf(fd, "SETS FOUND\n");
	return (set_1);
}

t_path	**edmonds(t_graph *g)
{
	t_path **set_1;
	int		paths;


	g->max_paths = count_max_paths(g);
	paths = 0;
	set_1 = ft_memalloc(sizeof(t_path*) * g->room_total);
	set_1[paths++] = bfs(g, 1, 0, g->room_total - 1);
	mod_edgeweight_path(g, set_1[paths - 1]);
	while (set_1[paths - 1])
	{
		set_1[paths++] = bfs(g, 1, 0, g->room_total - 1);
		mod_edgeweight_path(g, set_1[paths - 1]);
		print_rooms(g);
	}
	print_matrix(g->weight_m, g->room_total);
	//free and stuff
	set_1 = bfs_set(g, 2, 0, g->room_total - 1);
	return (set_1);
}

*/

/*
**	Do BFS one at a time. The rooms max flow capacity is edges - 1.
**	while (bfs(merge sort edge values acending))
**		modify path edges
**  return (bfs_set(use edges with value > 0. Prioritize rooms with flow 1/1))
**
*/

void	clean_set(t_path **set, t_graph *g)
{
	int i;

	i = -1;
	while (set[++i])
		clean_path(set[i], g);

}

t_path	**sorted_search(t_graph *g)
{
	t_path *shortest;
	t_path **set;

	shortest = bfs_new(g, 1, 0, g->room_total - 1);
	mod_edgeweight_path(g, shortest);
	print_matrix(g->weight_m, g->room_total * 2);
	while (shortest)
	{
		shortest = bfs_new(g, 1, 0, g->room_total - 1);
		//free path
		mod_edgeweight_path(g, shortest);
		print_matrix(g->weight_m, g->room_total * 2);
	//	sort_adlist_array(g);
	}
	g->max_paths = count_max_paths(g);
	set = bfs_set(g, 0, g->room_total - 1);
	clean_set(set, g);
	return (set);
}

/*

t_path **set_search_to_modifyPaths(t_graph *g)
{
	t_path **set_1;
	t_path *shortest;

	g->max_paths = count_max_paths(g);
	shortest = bfs(g, 1, 0, g->room_total - 1);
	mod_edgeweight_path(g, shortest);
	bfs_set_weightend(g, 1, 0 , g->room_total - 1);
	set_1 = bfs_set(g, 2, 0 , g->room_total - 1);
	return (set_1);
}

*/
/*
** Returns a paths set with one path with a length of 0. This leads to all ants to be able to flow straight to
** the end room in one line.
*/

t_path **unlimited_flow(void)
{
	t_path	**no_rooms;

	no_rooms = ft_memalloc(sizeof(t_path*) * 2);
	no_rooms[0] = ft_memalloc(sizeof(t_path));
	no_rooms[0]->len = 0;
	return (no_rooms);
}
