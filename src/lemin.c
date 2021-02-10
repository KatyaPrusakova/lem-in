/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/10 15:19:17 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_graph*		lem_in(char **line, t_graph* graph)
{
	int		i;

	parse_ants(line[0], graph);
	i = parse_room(line, graph);
	ft_dprintf(fd, "rooms: %d\n", i); // test
	parse_link(i, line, graph);

	ft_dprintf(fd, "\n");
	print_rooms(graph);
	find_paths(graph);

	return (graph); // change
}

int				main(int argc, char **argv)
{
	t_graph*	data;
	char		**line;

	// test
	fd = open("lemin.txt", O_RDWR);
	if (!fd)
		ft_printf("error opening file");
	// test

	if (argc < 1)
		return (0);
	line = parse_input(argv);
	data = create_graph(count_rooms(line));
	if (argc == 2 && !ft_strcmp(argv[1], "-v"))
	{
		ft_printf("visualizer activated\n"); //test
		data->visualize = 1;
	}
	lem_in(line, data);
	return (0);
}
