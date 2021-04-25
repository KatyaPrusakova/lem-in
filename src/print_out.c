/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/04/25 13:22:41 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_rooms(t_graph *graph)
{
	int		i;
	t_room	*tmp;

	i = 0;
	while (graph->adlist[i])
	{
		ft_dprintf(fd, "%d |%s|", i, graph->adlist[i]->name);
		if (graph->adlist[i]->next != NULL)
		{
			tmp = graph->adlist[i];
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
				ft_dprintf(fd, " -> |%s|%d", tmp->name, tmp->index);
			}
		}
		ft_dprintf(fd, " OUT: %d", graph->adlist[i]->out);
		ft_dprintf(fd, "\n");
		i++;
	}
}

void		print_input(char **line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		ft_printf("%s\n", line[i]);
	}
	ft_printf("\n");
}

int			print_error(int opt, char **input)
{
	if (input)
		ft_free2d((void**)input);
	if (opt == 0)
		exit(0);
	if (opt == 1)
		write(1, "run away\n", 10);
	if (opt == 2)
		write(1, "malloc failed\n", 15);
	if (opt == 3)
		write(1, "ants number is wrong\n", 22);
	if (opt == 4)
		write(1, "room is wrong\n", 15);
	if (opt == 5)
		write(1, "link is wrong\n", 15);
	if (opt == 6)
		write(1, "comment is wrong\n", 18);
	if (opt == 7)
		write(1, "empty line in the map file\n", 28);
	if (opt == 8)
		write(1, "map file is not valid\n", 23);
	if (opt == 9)
		write(1, "count room is wrong\n", 21);
	if (opt == 10)
		write(1, "invalid map\n", 13);
	exit(0);
}
