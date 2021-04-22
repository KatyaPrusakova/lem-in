/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:12:19 by eprusako          #+#    #+#             */
/*   Updated: 2021/04/22 14:27:21 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				create_edge(char **room_name, int  *adlist_index, t_graph* data)
{
	//ft_dprintf(fd, "l%s l %s\n", room[0], room[1]); //

	link_rooms(room_name[1], adlist_index[0], data);
	link_rooms(room_name[0], adlist_index[1], data);
	add_index_to_edge(data, room_name[1], adlist_index[1], adlist_index[0]);
	add_index_to_edge(data, room_name[0], adlist_index[0], adlist_index[1]);
	free(adlist_index);
	return (1);
}

int				link_rooms(char *room, int i, t_graph* data)
{
	t_room	*new;
	t_room	*tmp;

	if (!(new = ft_memalloc(sizeof(t_room))))
		print_error(2, NULL);
	tmp = data->adlist[i];
	if (tmp->next)
	{
		while (tmp->next != NULL)
		{
			if (!(ft_strcmp(tmp->next->name,room))) //if link already exists
			{ // add free
				print_error(5, NULL);
			}
			tmp = tmp->next;
		}
	}
	tmp->next = new;
	new->name = room;
	new->next = NULL;
	return (1);
}

void			add_index_to_edge(t_graph* data, char *name, int index, int i)
{
	t_room	*tmp;

	tmp = data->adlist[i];
	while (tmp)
	{
		if (tmp->name == name)
		{
			tmp->index = index;
//			tmp->end = data->adlist[index]->end;
			return;
		}
		tmp = tmp->next;
	}
}

int			*edge_index(int i, char **room, t_graph* graph)
{
	int		link_name;
	int		*index;

	link_name = 0;
	index = ft_memalloc(sizeof(int) * 2);
	while (i < graph->room_total)
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
		i++;
	}
	if (link_name != 2)
		print_error(5, NULL);
	return (index);
}

int			parse_link(int i, char **input, t_graph* graph)
{
	char	**room;
	char	*start;
	char	*end;
	int		s;
	int		e;

	s = 0;
	e = 0;
	start =  graph->adlist[0]->name;
	end =  graph->adlist[graph->room_total - 1]->name;
	while (input[i] && (ft_strchr(input[i], '-') || input[i][0] == '#')) //  add comment function
	{
		if (ft_strchr(input[i], '-'))
		{
			room = ft_strsplit(input[i], '-');
			create_edge(room, edge_index(0, room, graph), graph);
		}
		if (!ft_strcmp(room[0], start) || !ft_strcmp(room[1], start))
			s = 1;
		if (!ft_strcmp(room[0], end) || !ft_strcmp(room[1], end))
			e = 1;
		i++;
	}
	if (input[i]) // "\n" line
		print_error(10, input);
	return (s + e == 2 ? 1 : print_error(5, input));
}
