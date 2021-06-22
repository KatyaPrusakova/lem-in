/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/06/22 23:41:03 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// #link1-link2 gives an error as invalid link

t_graph	*lem_in(t_graph *g, char **input)
{
	t_path	**set;

	print_input(input);
	if (!g->unlimited_flow)
	{
		set = edmonds_karp(g);
		if (!set)
		{
			free_data(g, input);
			print_error(8, NULL);
		}
		if (g->visualize)
			ft_printf("\n");
		move_ants(set, g);
		free_path_set(&set);
	}
	else
	{
		print_input(input);
		move_all_to_end(g->ants, g->adlist[g->room_total - 1]->name);
	}
	return (g);
}

int	main(int argc, char **argv)
{
	t_graph		*data;
	char		**line;

	g_fd = open("lemin.txt", O_RDWR);
	if (!g_fd)
		print_error(1, NULL);
	if (argc < 1)
		return (0);
	line = parse_input();
	data = create_graph(count_rooms(line), line);
	if (argc > 1 && !ft_strcmp(argv[1], "-v"))
		data->visualize = 1;
	lem_in(data, line);
	free_data(data, line);
	return (0);
}
