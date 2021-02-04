/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/05 00:39:17 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			add_room(int flag, char *room_name, t_graph *graph)
{
	int			i;
	t_room		*new;

	i = 1;
	if (!(new = ft_memalloc(sizeof(t_room))))
		ft_error(2);
	if (!flag)
	{
		while (graph->adlist[i])
			i++;
		graph->adlist[i] = new;
		//printf("add_room %d|%s|%d\n", i, graph->adlist[i]->name, graph->room_count);
	}
	else if (flag == 1)
	{
		graph->adlist[0] = new;
	}
	// else if (flag == 2)
	// {
	// 	graph->adlist[graph->room_total-2] = new;
	// }
	new->name = room_name;
}

t_graph*		create_graph(int rooms)
{
	t_graph		*new;

	new = ft_memalloc(sizeof(t_graph));
	new->adlist = ft_memalloc(sizeof(t_room*) * (rooms+1));
	new->room_total = rooms;
	return (new);
}

//should it exit when 0 ants?
void				ft_ants_num(char *line, t_graph* data)
{
	if (!(ft_strisdigit(line)))
		ft_error(2); //check
	data->ants = ft_atoi(line);
}

int				link_rooms(char *room, int i, t_graph* data)
{
	t_room	*new;
	t_room	*tmp;

	if (!(new = ft_memalloc(sizeof(t_room))))
		ft_error(2);
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



void				add_index_to_room(t_graph* data, char *name, int index, int i)
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

int				ft_link(char *line, t_graph* data)
{
	int		i;
	int		flag;
	int		index[2];
	char	**room;

	i = 0;
	flag = 0;
	room = ft_strsplit(line, '-');
	//0-2 nana-lala nana = 1 ADD INDEX to notes
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
	//printf("index f %d| %s|%s \n", index[0], room[0], room[1]);
	add_index_to_room(data, room[1], index[1], index[0]);
	add_index_to_room(data, room[0], index[0], index[1]);
	return (flag == 2 ? 1 : ft_error(5));
}

char*				ft_room(char *line)
{
	char	**room;

	if (line[0] == 'L')
		ft_error(4);
	room = ft_strsplit(line, ' ');
	if (!room[0] || room[3] || !ft_strisdigit(room[1]) || !ft_strisdigit(room[2]))
		ft_error(4);
	//add_room(room[0], &new ,data);

//	printf("ft room %s\n", room[0]);
	return (room[0]);
}

//function to add rooms and names

char			*ft_firstword(char **line, int i)
{
	char	**room;

	room = ft_strsplit(line[i], ' ');

	return (room[0]);
}

int				ft_error(int opt)
{
//	dont forget to free(data);
	if (opt == 0)
		exit(0);
	if (opt == 1)
		write(1, "run away\n", 10);
	if (opt == 2)
		write(1, "malloc failed\n", 15);
	if (opt == 3)
		write(1, "ants number is wrong\n", 22);
	if (opt == 4)
		write(1, "room is wrong\n", 22);
	if (opt == 5)
		write(1, "link is wrong\n", 15);
	if (opt == 6)
		write(1, "comment is wrong\n", 18);
	if (opt == 7)
		write(1, "empty line in the map file\n", 28);
	if (opt == 8)
		write(1, "map file is not valid\n", 23);
	exit(0);
}

t_graph*		lem_in(char **line, t_graph* graph) 
{
	int		i;

	parse_ants(line[0], graph);
	i = parse_room(line, graph);
	parse_link(i, line, graph);

	//bfs(graph, 1);

	printf("\n");
	print_rooms(graph);

	return (graph); // change
}

int				main(int argc, char **argv)
{
	t_graph*	data;
	char		**line;

	if (argc < 1)
		return (0);
	line = parse_input(argv);
	data = create_graph(count_rooms(line));
	lem_in(line, data);
//	printf("end of program\n");
	return (0);
}
