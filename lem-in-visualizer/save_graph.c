/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:49:29 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/01 23:06:21 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

//rooms[1].name not allocated.

int		edge_index(t_room *rooms, char *name)
{
	int i;

	i = 0;
	while (ft_strcmp(name, rooms[i].name))
		i++;
	return (i);
}

t_data	scale_map(char **input)
{
	t_data	new;
	char	**split;
	int		i;
	int		nb;

	ft_bzero(&new, sizeof(t_data));
	i = 0;
	new.ants = ft_atoi(input[0]);
	while (ft_strchr(input[++i], ' ') || input[i][0] == '#')
	{
		if (input[i][0] != '#')
		{
			new.room_count += 1;
//			ft_printf("input line %s\n", input[i]); //test
			split = ft_strsplit(input[i], ' ');
			if (!split)
				ft_error("ft_strsplit fail");
			if ((nb = ft_atoi(split[1])) > new.max_x)
				new.max_x = nb;
			if ((nb = ft_atoi(split[2])) > new.max_y)
				new.max_y = nb;
			ft_free2d((void**)split);
		}
	}
//	ft_printf("i = %d\n", i);
	return (new);
}

t_room		add_room(char *line, int index)
{
	t_room	new;
	char	**split;

	split = ft_strsplit(line, ' ');
	if (!split)
		ft_error("split fail");
	new.name = ft_strdup(split[0]);
	if (!new.name)
		ft_error("strdup fail");
	new.path = 0;
	new.x = ft_atoi(split[1]);
	new.y = ft_atoi(split[2]);
	new.q = -1;
	new.index = index;
	new.visited_from = -1;
	ft_free2d((void**)split);
	return (new);
}

t_edge		*new_edge(t_edge *head, t_room *rooms, char *src, char *dst)
{
	t_edge	*new;
	t_edge	*tmp;

	new = ft_memalloc(sizeof(t_edge));
	if (!new)
		ft_error("malloc fail");
	new->src = edge_index(rooms, src);
	new->dst = edge_index(rooms, dst);
	new->rgba = RGBA_VOID;
	new->next = NULL;
	if (!head)
		return (new);
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		return (head);
	}
}

t_edge		*add_edges(t_room *rooms, char **input, int room_count)
{
	char	**split;
	t_edge	*head;

	head = NULL;
	while (!ft_strchr(input[room_count], '-'))
		room_count++;
	while(input[room_count] && ft_strchr(input[room_count], '-'))
	{
		if (!(split = ft_strsplit(input[room_count], '-')))
			ft_error("split fail");
//		ft_printf("split0 = %s, split1 = %s\n", split[0], split[1]);
//		ft_printf("tttttttttttttttttttttttttttttttttttt\n");
		head = new_edge(head, rooms, split[0], split[1]);
		free(split);
		room_count++;
	}
	return (head);
}

//test

void		print_edges(t_edge *list)
{
	while (list)
	{
		ft_printf("EDGE: src: %s dst %s\n", list->src, list->dst);
		list = list->next;
	}
}

t_map		save_rooms(char **input, int room_count)
{
	int		i;
	int		j;
	t_map	list;

	i = 1;
	j = 0;
	if (!(list.rooms = ft_memalloc(sizeof(t_room) * (room_count + 1))))
		ft_error("Malloc fail");
	list.count = room_count;
	while (!ft_strchr(input[i], '-'))
	{
		if (!ft_strcmp(input[i], "##start"))
			list.rooms[0] = add_room(input[++i], 0);
		else if (!ft_strcmp(input[i], "##end"))
			list.rooms[room_count - 1] = add_room(input[++i], room_count - 1);
		else if (input[i][0] != '#')
		{
			j++;
			list.rooms[j] = add_room(input[i], j);
		}
//		ft_printf("test\n");
		i++;
	}

	// test
	i = 0;
	while (i < list.count)
	{  //test
	//	ft_printf("test");
	//	ft_printf("room n%d = %s\n", i, list.rooms[i].name);
		i++;
	} //test
	// test
	list.edges = add_edges(list.rooms, input, room_count);
	//print_edges(list.edges);
	return (list);
}
