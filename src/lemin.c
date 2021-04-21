/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/04/21 18:54:45 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			set_room_capacity(t_graph * g)
{
	t_room	*tmp;
	int		edges;
	int		i;

	i = 0;
	while (i < g->room_total)
	{
		tmp = g->adlist[i];
		edges = -1;
		while (tmp->next)
		{
			tmp = tmp->next;
			edges++;
		}
		g->adlist[i]->max_capacity = edges;
		g->adlist[i]->remaining_capacity = edges;
		i++;
	}
}

t_graph*		lem_in(char **line, t_graph* graph)
{
	int		i;
	t_path	**first_set;
	//test
	/*
	*/
	t_search s;
	ft_bzero(&s, sizeof(t_search));
	s.end = graph->room_total - 1;
	first_set = ft_memalloc(sizeof(t_path*) * graph->room_total);
	//test

	i = parse_ants(line, graph);
	//ft_dprintf(fd, "after_parse ant %s\n", line[i]); //test
	i = parse_room(i, line, graph);
	//ft_dprintf(fd, "lem_in  2%d\n", i); //test
	parse_link(i, line, graph);
	set_room_capacity(graph);
	//ft_dprintf(fd, "after parse link %d\n", graph->room_total); //test
	// ft_dprintf(fd, "\n");
	print_input(line);
//	print_rooms(graph); //test
	ft_dprintf(fd, "\n"); //test
//	first_set = find_paths(graph);
//	if (end_is_neighbour(graph->adlist[0]->next, graph->room_total - 1))
//		first_set = unlimited_flow();
//	else
	//	first_set = find_sets(graph);
	//first_set = edmonds(graph);
	//first_set = set_search_to_modifyPaths(graph);
	first_set = sorted_search(graph);
//	first_set[0] = dfs_find_path(graph, graph->adlist[0], s);
	if (graph->visualize)
		ft_printf("\n");
	//allocate_ants_to_rooms(first_set, graph);
	move_ants(first_set, graph);
	return (graph); // change
}

int				main(int argc, char **argv)
{
	t_graph*	data;
	char		**line;

	// test
	fd = open("lemin.txt", O_RDWR);
	if (argc)
//	fd_zero = open (argv[2], O_RDONLY);
	fd_zero = 0;
	if (!fd)
		ft_printf("error opening file");
	// test
//	if (!fd_zero)
//		ft_printf("error opening %s\n", argv[2]);
	if (argc < 1)
		return (0);
	line = parse_input();
	data = create_graph(count_rooms(line));
	if (argc > 1 && !ft_strcmp(argv[1], "-v"))
		data->visualize = 1;
	lem_in(line, data);
	return (0);
}
