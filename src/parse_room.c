/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:12:19 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/24 10:28:40 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Function to count rooms in order to malloc memory
** for addlist struct
*/

int				count_rooms(char **input)
{
	int		i;
	int		start_end;
	int		room;

	start_end = 0;
	room = 0;
	i = valid_ants(1, input);
	while (input[i] && !ft_strchr(input[i], '-'))
	{
		//ft_dprintf(fd, "|%s\n", line[i]); //test
		if (!ft_strcmp(input[i], "##start") || !ft_strcmp(input[i], "##end"))
			start_end++;
		if (ft_strchr(input[i], ' ') && input[i][0] != '#' && is_room(input, i))
			room++;
		i++;
	}
	ft_dprintf(fd, " count_rooms %d\n", room);
	start_end != 2 ?  print_error(8, input) : 0;
	return (room ? room : print_error(9, input));
}

/*
** Function to add rooms to the addlist struct
** flag 1 == start
** flag 2 == end
** !flag == rooms between start too end
*/

int			add_room(int flag, char *room_name, t_graph *graph)
{
	int			i;
	t_room		*new;

	i = 1;
	if (!(new = ft_memalloc(sizeof(t_room))))
		print_error(2, NULL);
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
	return  (1);
}

/*
** Function
** for addlist struct
*/

int			parse_room(int i, char **line, t_graph* graph)
{

	while (line[i] && !ft_strchr(line[i], '-'))  // add comment function
	{
		 // ft_dprintf(fd, "loop %s\n", line[i]); //test
			if (!ft_strcmp(line[i], "##start"))
				add_room(1, ft_firstword(line, ++i), graph);
			else if (!ft_strcmp(line[i], "##end"))
				add_room(2, ft_firstword(line, ++i), graph);
			else if (line[i][0]  == '#')
				i++;
			else
				add_room(0, ft_firstword(line, i), graph);
			i++;
	}
	
	if (ft_strchr(line[i-1], '-'))
		i--;
	return(i);
}

/*
** Function to check if room is valid
*/

char*			is_room(char **input, int i)
{
	char	**room;

	if (input[i][0] == 'L' || !input[i])
		print_error(4, input);
	room = ft_strsplit(input[i], ' ');
	// ft_dprintf(fd, "room |%s|%s|%s\n", room[0], room[1], room[2]); //test
	if (!room[0] || !room[1] || !room[2] || room[3] || !ft_strisdigit(room[1]) \
	|| !ft_strisdigit(room[2]))
		print_error(4, input);
	return (room[0]);
}

char			*ft_firstword(char **line, int i)
{
	char	**room;

	room = ft_strsplit(line[i], ' ');
	return (room[0]);
}
