/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/15 13:08:12 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_graph*		lem_in(char **line, t_graph* graph)
{
	int		i;


	i = parse_ants(line, graph);
	
	//ft_dprintf(fd, "after_parse ant %s\n", line[i]); //test
	
	i = parse_room(i, line, graph);
	//ft_dprintf(fd, "lem_in  2%d\n", i); //test
	
	parse_link(i, line, graph);

	//ft_dprintf(fd, "after parse link %d\n", graph->room_total); //test
	// ft_dprintf(fd, "\n");
	print_input(line);
	print_rooms(graph); //test
	ft_dprintf(fd, "\n"); //test
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
	line = parse_input();//argv 
	data = create_graph(count_rooms(line));
	//ft_dprintf(fd, "graph %s\n", line[0]); //test
	if (argc == 2 && !ft_strcmp(argv[1], "-v"))
	{
	//	ft_printf("visualizer activated\n"); //test
		data->visualize = 1;
	}
	lem_in(line, data);
	return (0);
}
