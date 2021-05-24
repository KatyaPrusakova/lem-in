/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:12:19 by eprusako          #+#    #+#             */
/*   Updated: 2021/05/24 16:05:37 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** g->adlist is an array that contains linked lists.
** This function adds b to the end of the list in adlist[a]
** and a to the end of the list in adlist[b].
*/

int	link_to_adlist(int a, int b, t_graph *g)
{
	t_room	*new;
	t_room	*tmp;

	tmp = g->adlist[a];
	while (tmp->next)
	{
		if (tmp->index == b)
			print_error(5, NULL);
		tmp = tmp->next;
	}
	new = ft_memdup(g->adlist[b], sizeof(t_room));
	if (!new)
		print_error(2, NULL);
	new->index = b;
	new->next = NULL;
	tmp->next = new;
	return (1);
}

/*
** int *adlist_index contains the two rooms to be linked.
** in rooms are located in adlist[i]. Out rooms are located
** in adlist[i + total rooms in graph].
** Add edge for both rooms between room[i](in) - room[i + rooms_total](out).
** Add edge between room1.in - room.0 out both ways.
** Add edge between room0.in -room 1 out both ways.
*/

int	create_edge(int *adlist_index, t_graph *g)
{
	if (!adlist_index[0])
	{
		link_to_adlist(0, adlist_index[1], g);
		return (1);
	}
	if (!adlist_index[1])
	{
		link_to_adlist(0, adlist_index[0], g);
		return (1);
	}
	link_to_adlist(adlist_index[0], adlist_index[1] + g->room_total, g);
	link_to_adlist(adlist_index[1] + g->room_total, adlist_index[0], g);
	link_to_adlist(adlist_index[1], adlist_index[0] + g->room_total, g);
	link_to_adlist(adlist_index[0] + g->room_total, adlist_index[1], g);
	return (1);
}

/*
** **room contains the names of the rooms that are linked.
** Comparing the room names to the names in the adlist array.
** Returns the indexes of the rooms as an allocated int[2].
*/

int	*edge_index(char **room, t_graph *graph)
{
	int		link_name;
	int		*index;
	int		i;

	link_name = 0;
	i = -1;
	index = ft_memalloc(sizeof(int) * 2);
	if (!index)
		print_error(2, NULL);
	while (++i < graph->room_total)
	{
		if (!(ft_strcmp(graph->adlist[i]->name, room[0])))
		{
			index[0] = i;
			link_name++;
		}
		if (!(ft_strcmp(graph->adlist[i]->name, room[1])))
		{
			index[1] = i;
			link_name++;
		}
	}
	if (link_name != 2)
		print_error(5, NULL);
	return (index);
}

/*
** Creating out-rooms for every room in the graph.
*/

void	create_room_capacity(t_graph *g)
{
	int	i;

	i = 1;
	while (i < g->room_total - 1)
	{
		link_to_adlist(i, i + g->room_total, g);
		link_to_adlist(i + g->room_total, i, g);
		i++;
	}
}

/*
** Reading the lines that have the links seperated by '-'.
** Getting the edge index numbers from the names in edge_index().
** Adding the edges to the adjacency list in create_edge().
*/

int	parse_links(int i, char **input, t_graph *g)
{
	char	**rooms_to_link;
	int		*edges;

	create_room_capacity(g);
	while (input[i] && (ft_strchr(input[i], '-') || input[i][0] == '#'))
	{
		if (ft_strchr(input[i], '-'))
		{
			rooms_to_link = ft_strsplit(input[i], '-');
			edges = edge_index(rooms_to_link, g);
			if ((edges[0] == 0 && edges[1] == g->room_total - 1)
				|| (edges[1] == 0 && edges[0] == g->room_total - 1))
			{
				g->unlimited_flow = 1;
				return (1);
			}
			create_edge(edges, g);
			ft_free2d((void **)rooms_to_link);
			ft_memdel((void **)&edges);
		}
		i++;
	}
	if (input[i])
		print_error(10, input);
	return (1);
}
