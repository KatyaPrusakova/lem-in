/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:53:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/02 17:06:13 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Prints the current state of queue to stdout.
*/

void	draw_queue(t_room **adlist, t_queue *q)
{
	t_room	*tmp;

	if (!adlist)
		ft_printf("unused variable");
	tmp = q->head;
	if (!q || !tmp)
	{
		return;
	}
	while (tmp)
	{
		ft_printf("%d-%d ", tmp->prev_room_index, tmp->index);
		tmp = tmp->next;
	}
	ft_n(1);
}

/*
** Returns the possible paths, starting from the shortest path[0].
*/


t_path		**find_paths(t_graph *graph)
{
	t_path		**paths;
	int			rooms_in_paths;
	int			max_paths;

	max_paths = count_paths(graph);
	paths = ft_memalloc(sizeof(t_path*) * graph->room_total);
//	if (!paths)
//		ft_error(2);
	if (graph->visualize)
		ft_printf("BFS\n");
	paths[0] = bfs(max_paths, graph, graph->adlist[0]);
	rooms_in_paths = calculate_set_lenght(paths);
	if (rooms_in_paths >= graph->ants)
		return (paths);
	// free saved path
	print_matrix(graph->weight, graph->room_total);
	if (graph->visualize)
		ft_printf("BFS\n");
	paths[0] = bfs(max_paths, graph, graph->adlist[0]);
	if (graph->visualize)
		ft_printf("BFS\n");
	// while < max_paths!!!
	paths = bfs_3(max_paths, graph, graph->adlist[0]);

	//print_paths(paths);
	allocate_ants_to_rooms(paths, graph);
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
