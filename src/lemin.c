/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/04/27 15:26:51 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_graph			*lem_in(t_graph *graph)
{
	t_path	**first_set;

	first_set = sorted_search(graph);
	if (graph->visualize)
		ft_printf("\n");
	move_ants(first_set, graph);
	free_path_set(&first_set);
	return (graph);
}

int				main(int argc, char **argv)
{
	t_graph		*data;
	char		**line;

	fd = open("lemin.txt", O_RDWR);
	if (!fd)
		print_error(1, NULL);
	if (argc < 1)
		return (0);
	line = parse_input();
	data = create_graph(count_rooms(line), line);
	print_rooms(data);
	print_input(line);
	if (argc > 1 && !ft_strcmp(argv[1], "-v"))
		data->visualize = 1;
	lem_in(data);
	free_data(data, line);
	return (0);
}
