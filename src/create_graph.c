/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:51:11 by ksuomala          #+#    #+#             */
/*   Updated: 2021/06/07 20:54:27 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_graph	*create_graph(int rooms, char **line)
{
	t_graph		*new;
	int			i;

	new = ft_memalloc(sizeof(t_graph));
	new->adlist = ft_memalloc(sizeof(t_room *) * (rooms * 2 + 1));
	new->room_total = rooms;
	new->weight_m = create_matrix(rooms * 2, rooms * 2);
	i = parse_ants(line, new);
	i = parse_room(i, line, new);
	if (!parse_links(i - 1, line, new))
	{
		free_data(new, line);
		print_error(5, NULL);
	}
	return (new);
}
