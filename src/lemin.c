/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/05/31 15:53:59 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// #link1-link2 gives an error as invalid link

t_graph	*lem_in(t_graph *g)
{
	t_path	**set;

	if (!g->unlimited_flow)
	{
		set = edmonds_karp(g);
		if (!set)
			print_error(1, NULL);
		if (g->visualize)
			ft_printf("\n");
		print_paths(set, g->adlist); //test
		move_ants(set, g);
		free_path_set(&set);
	}
	else
		move_all_to_end(g->ants, g->adlist[g->room_total - 1]->name);
	return (g);
}

int	main(int argc, char **argv)
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
	print_input(line);
	if (argc > 1 && !ft_strcmp(argv[1], "-v"))
		data->visualize = 1;
	lem_in(data);
	free_data(data, line);
	return (0);
}
