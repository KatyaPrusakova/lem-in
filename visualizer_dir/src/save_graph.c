/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:49:29 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/19 19:01:48 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

//rooms[1].name not allocated.

void		print_edges(t_room *rooms, int rooms_total)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < rooms_total)
	{
		ft_putnbr(i);
		write(1, ":|", 2);
		while (rooms[i].adlist[j])
		{
			ft_putnbr(rooms[i].adlist[j]);
			write(1, "|", 1);
			j++;
		}
		ft_n(1);
		j = 0;
		i++;
	}
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
	new.level = 0;
	ft_bzero(new.adlist, sizeof(int) * 10000);
	new.visited = -1;
	ft_free2d((void**)split);
	return (new);
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
//		//ft_printf("test\n");
		i++;
	}

	// test
	i = 0;
	while (i < list.count)
	{  //test
	//	//ft_printf("test");
	//	//ft_printf("room n%d = %s\n", i, list.rooms[i].name);
		i++;
	} //test
	// test
	list.edges = add_edges(list.rooms, input, room_count);
	//print_edges(list.rooms, room_count);
	//print_edges(list.edges);
	return (list);
}
