/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:12:19 by eprusako          #+#    #+#             */
/*   Updated: 2021/04/27 15:23:48 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		link_to_adlist(int a, int b, t_graph *g)
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

int		create_edge(int *adlist_index, t_graph *g)
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

int		*edge_index(char **room, t_graph *graph)
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

void	create_room_capacity(t_graph *g)
{
	int i;

	i = 1;
	while (i < g->room_total - 1)
	{
		link_to_adlist(i, i + g->room_total, g);
		link_to_adlist(i + g->room_total, i, g);
		i++;
	}
}

int		parse_links(int i, char **input, t_graph *g)
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
			create_edge(edges, g);
			ft_free2d((void**)rooms_to_link);
			ft_memdel((void**)&edges);
		}
		i++;
	}
	if (input[i])
		print_error(10, input);
	return (1);
}
