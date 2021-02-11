/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:12:19 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/11 12:30:00 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Function to count rooms in order to malloc memory
** for addlist struct
*/

int				count_rooms(char **line)
{
	int		i;
	int		start_end;
	int		room;

	i = 0;
	start_end = 0;
	room = 0;
	while (line[i])
	{
		if (!ft_strcmp(line[i], "##start") || !ft_strcmp(line[i], "##end"))
			start_end++;
		if (ft_strchr(line[i], ' ') && line[i][0] != '#' && is_room(line[i]))
			room++;
		i++;
	}
	printf("%d\n", room);
	start_end != 2 ?  print_error(8) : 0;
	return (room ? room : print_error(9));
}

/*
** Function to add rooms to the addlist struct
** flag 1 == start
** flag 2 == end
** !flag == rooms between start too end
*/

void			add_room(int flag, char *room_name, t_graph *graph)
{
	int			i;
	t_room		*new;

	i = 1;
	if (!(new = ft_memalloc(sizeof(t_room))))
		print_error(2);
	new->prev_room_index = -1;
	if (flag == 1)
		graph->adlist[0] = new;
	else if (flag == 2)
	{
		graph->adlist[graph->room_total - 1] = new;
		graph->adlist[graph->room_total - 1]->end = 1;
		graph->adlist[graph->room_total - 1]->index = graph->room_total - 1;
	}
	else
	{
		while (graph->adlist[i])
			i++;
		graph->adlist[i] = new;
		graph->adlist[i]->index = i;
	}
	new->name = room_name;
}

/*
** Function
** for addlist struct
*/

int			parse_room(char **line, t_graph* graph)
{
	int		i;

	i = 0;
	while (line[++i] && !ft_strchr(line[i], '-'))  // add comment function
	{
		//printf("%s\n", line[i]);
			if (!ft_strcmp(line[i], "##start"))
				add_room(1, ft_firstword(line, ++i), graph);
			else if (!ft_strcmp(line[i], "##end"))
				add_room(2, ft_firstword(line, ++i), graph);
			else if (line[i][0]  == '#')
				i++;
			else
				add_room(0, ft_firstword(line, i), graph);
	}
	return(i);
}

/*
** Function to check if room is valid
*/

char*			is_room(char *line)
{
	char	**room;

	if (line[0] == 'L' || !line)
		print_error(4);
	room = ft_strsplit(line, ' ');
	printf("room |%s|%s|%s\n", room[0], room[1], room[2]);
	if (!room[0] || room[3] || !ft_strisdigit(room[1]) \
	|| !ft_strisdigit(room[2]))
		print_error(4);
	return (room[0]);
}

char			*ft_firstword(char **line, int i)
{
	char	**room;

	room = ft_strsplit(line[i], ' ');
	return (room[0]);
}
