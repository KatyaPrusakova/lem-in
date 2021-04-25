/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:12:19 by eprusako          #+#    #+#             */
/*   Updated: 2021/04/25 14:01:23 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Function to count rooms in order to malloc memory
** for addlist struct
*/

int			count_rooms(char **input)
{
	int		i;
	int		start_end;
	int		room;

	start_end = 0;
	room = 0;
	i = valid_ants(1, input);
	while (input[i] && !ft_strchr(input[i], '-'))
	{
		if (!ft_strcmp(input[i], "##start") || !ft_strcmp(input[i], "##end"))
			start_end++;
		if (ft_strchr(input[i], ' ') && input[i][0] != '#' && is_room(input, i))
			room++;
		i++;
	}
	start_end != 2 ? print_error(8, input) : 0;
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

	if (!(new = ft_memalloc(sizeof(t_room))))
		print_error(2, NULL);
	new->prev_room_index = -1;
	if (flag == 1)
		i = 0;
	else if (flag == 2)
		i = graph->room_total - 1;
	else
	{
		i = 1;
		while (graph->adlist[i])
			i++;
	}
	graph->adlist[i] = new;
	graph->adlist[i]->index = i;
	new->name = room_name;
	graph->adlist[graph->room_total + i] = ft_memdup(new, sizeof(t_room));
	if (graph->adlist[graph->room_total + i] == NULL)
		print_error(2, NULL);
	graph->adlist[graph->room_total + i]->out = 1;
	graph->adlist[graph->room_total + i]->index = graph->room_total + i;
	return (1);
}

/*
** Function
** for addlist struct
*/

int			parse_room(int i, char **line, t_graph *graph)
{
	while (line[i] && !ft_strchr(line[i], '-'))
	{
		if (!ft_strcmp(line[i], "##start"))
			add_room(1, first_word(line, ++i), graph);
		else if (!ft_strcmp(line[i], "##end"))
			add_room(2, first_word(line, ++i), graph);
		else if (line[i][0] == '#')
			i++;
		else
			add_room(0, first_word(line, i), graph);
		i++;
	}
	graph->adlist[0]->out = 1;
	if (ft_strchr(line[i - 1], '-'))
		i--;
	return (i);
}

/*
** Function to check if room is valid
*/

char		*is_room(char **input, int i)
{
	char	**room;

	if (input[i][0] == 'L' || !input[i])
		print_error(4, input);
	room = ft_strsplit(input[i], ' ');
	if (!room[0] || !room[1] || !room[2] || room[3] ||
	!ft_isnumeric_str(room[1]) || !ft_isnumeric_str(room[2]))
		print_error(4, input);
	return (room[0]);
}

char		*first_word(char **line, int i)
{
	char	**room;

	room = ft_strsplit(line[i], ' ');
	return (room[0]);
}
