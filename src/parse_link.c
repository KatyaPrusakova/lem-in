/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:12:19 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/14 23:11:33 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				is_link(char **room, t_graph* data)
{
	int		i;
	int		flag;
	int		index[2];

	i = 0;
	flag = 0;
	while (data->adlist[i])
	{
		//ft_dprintf(fd, "l%s l %s\n", room[0], room[1]); //
		if (!(ft_strcmp(data->adlist[i]->name, room[0])))
		{
			flag += link_rooms(room[1], i, data);
			index[0] = i;
		}
		if (!(ft_strcmp(data->adlist[i]->name, room[1])))
		{
			flag += link_rooms(room[0], i, data);
			index[1] = i;
		}
		i++;
	}
	add_index_to_room(data, room[1], index[1], index[0]);
	add_index_to_room(data, room[0], index[0], index[1]);
	return (flag == 2 ? 1 : print_error(5));
}

int				link_rooms(char *room, int i, t_graph* data)
{
	t_room	*new;
	t_room	*tmp;

	if (!(new = ft_memalloc(sizeof(t_room))))
		print_error(2);
	tmp = data->adlist[i];
	if (tmp->next)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	tmp->next = new;
	new->name = room;
	new->next = NULL;
	return (1);
}

void			add_index_to_room(t_graph* data, char *name, int index, int i)
{
	t_room	*tmp;

	tmp = data->adlist[i];
	while (tmp)
	{
		if (tmp->name == name)
		{
			tmp->index = index;
			tmp->end = data->adlist[index]->end;
			return;
		}
		tmp = tmp->next;
	}
}

int			parse_link(int i, char **line, t_graph* graph)
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
	while (line[i] && (ft_strchr(line[i], '-') || line[i][0] == '#')) //  add comment function
	{
		//ft_dprintf(fd, "ff %s\n", line[i]);
		if (ft_strchr(line[i], '-'))
		{	
			room = ft_strsplit(line[i], '-');
			is_link(room, graph);
		}
		if (!ft_strcmp(room[0], start) || !ft_strcmp(room[1], start))
			s = 1;
		if (!ft_strcmp(room[0], end) || !ft_strcmp(room[1], end))
			e = 1;
		i++;
	}
	return (s + e == 2 ? 1 : print_error(5));
}
