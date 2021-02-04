/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:12:19 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/05 00:21:47 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				is_link(char *line, t_graph* data)
{
	int		i;
	int		flag;
	int		index[2];
	char	**room;

	i = 0;
	flag = 0;
	room = ft_strsplit(line, '-'); 
	while (data->adlist[i])
	{
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
	return (1);
}

void			add_index_to_room(t_graph* data, char *name, int index, int i)
{
	t_room	*tmp;
	

	tmp = data->adlist[i];
	//printf("data->adlist[%d]\n", i);
	while (tmp)
	{
	//	printf("tmp %s|%s %d\n", tmp->name, name, index);
		if (tmp->name == name)
		{
			tmp->index = index;
			return;
		}
		tmp = tmp->next;
	}
}

void			parse_link(int i, char **line, t_graph* graph)
{
//	printf("start linking %s\n", line[i]);
	while (line[i] && (ft_strchr(line[i], '-') || line[i][0] == '#')) //  add comment function
	{
		if (ft_strchr(line[i], '-'))
			is_link(line[i], graph);
		i++;
	}
}