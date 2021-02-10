/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:07 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_graph*		lem_in(char **line, t_graph* graph)
{
	int		i;

	parse_ants(line[0], graph);
	i = parse_room(line, graph);
	ft_printf("rooms: %d\n", i); // test
	parse_link(i, line, graph);

	printf("\n");
	print_rooms(graph);
	find_paths(graph);

	return (graph); // change
}

int				main(int argc, char **argv)
{
	t_graph*	data;
	char		**line;

	if (argc < 1)
		return (0);
	line = parse_input(argv);
	data = create_graph(count_rooms(line));

	lem_in(line, data);
	return (0);
}
