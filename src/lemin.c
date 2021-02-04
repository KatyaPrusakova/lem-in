/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/05 00:30:00 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				print_error(int opt)
{
//	dont forget to free(data);
	if (opt == 0)
		exit(0);
	if (opt == 1)
		write(1, "run away\n", 10);
	if (opt == 2)
		write(1, "malloc failed\n", 15);
	if (opt == 3)
		write(1, "ants number is wrong\n", 22);
	if (opt == 4)
		write(1, "room is wrong\n", 22);
	if (opt == 5)
		write(1, "link is wrong\n", 15);
	if (opt == 6)
		write(1, "comment is wrong\n", 18);
	if (opt == 7)
		write(1, "empty line in the map file\n", 28);
	if (opt == 8)
		write(1, "map file is not valid\n", 23);
	exit(0);
}

t_graph*		lem_in(char **line, t_graph* graph) 
{
	int		i;

	parse_ants(line[0], graph);
	i = parse_room(line, graph);
	parse_link(i, line, graph);

	//bfs(graph, 1);

	printf("\n");
	print_rooms(graph);

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
//	printf("end of program\n");
	return (0);
}