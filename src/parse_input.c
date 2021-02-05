/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/05 16:35:52 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char			**parse_input(char **av)
{
	int		i;
	char	**line;
//	int		room;

	i = 0;
//	room = 0;
	av[0] = NULL; // delete if av not needed
	line = ft_memalloc(sizeof(char*) * 100); // if goes to 101 malloc more
	while (get_next_line(0, &line[i]) == 1)
	{
		if (!line[i][0])
			print_error(7);
		i++;
	}
	if (!i)
		print_error(8);
	return (line);
}
