/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link_ks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:12:34 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/22 15:27:49 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"



int			link_rooms(int a, int b, t_graph* g)
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

int			create_edges(int *adlist_index, t_graph *g)
{
	link_rooms(adlist_index[0], adlist_index[1] + g->room_total, g);
	link_rooms(adlist_index[1] + g->room_total, adlist_index[0], g);
	link_rooms(adlist_index[1], adlist_index[0] + g->room_total, g);
	link_rooms(adlist_index[0] + g->room_total, adlist_index[1], g);
	free(adlist_index);
	return (1);
}

int			*edge_index(char **room, t_graph* graph)
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

void	create_room_edges(t_graph *g)
{
	int i;

	i = 1;
	ft_printf("Rooms total %d\n", g->room_total);
	while (i < g->room_total - 1)
	{
		link_rooms(i, i + g->room_total, g);
		link_rooms(i + g->room_total, i, g);
		i++;
	}
}


int		parse_links(int i, char **input, t_graph *g)
{
	char	**rooms_to_link;
	char	*start;
	char	*end;
	int		s;
	int		e;

	s = 0;
	e = 0;
	start = g->adlist[0]->name;
	end = g->adlist[g->room_total - 1]->name;
	create_room_edges(g);
	while (input[i] && (ft_strchr(input[i], '-') || input[i][0] == '#'))
	{
		ft_printf("test\n");
		if (ft_strchr(input[i], '-'))
		{
			rooms_to_link = ft_strsplit(input[i], '-');
			create_edges(edge_index(rooms_to_link, g), g);
		}
		if (!ft_strcmp(rooms_to_link[0], start) || !ft_strcmp(rooms_to_link[1], start))
			s = 1;
		if (!ft_strcmp(rooms_to_link[0], end) || ft_strcmp(rooms_to_link[1], end))
			e = 1;
		i++;
	}
	if (input[i])
	print_error(10, input);
	if (s + e == 2)
		return (1);
	return (0);
}
