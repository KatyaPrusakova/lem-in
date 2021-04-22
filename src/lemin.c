/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/04/22 15:17:24 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
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
*/

t_graph*		lem_in(t_graph* graph)
{
	t_path	**first_set;

	first_set = ft_memalloc(sizeof(t_path*) * graph->room_total);
	first_set = sorted_search(graph);
	if (graph->visualize)
		ft_printf("\n");
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
	data = create_graph(count_rooms(line), line);
	print_rooms(data);
	if (argc > 1 && !ft_strcmp(argv[1], "-v"))
		data->visualize = 1;
	lem_in(data);
	return (0);
}
