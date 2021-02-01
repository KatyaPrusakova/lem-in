/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/01 18:47:10 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room*			create_room(t_graph *graph) 
{
	t_room		*new;

	if (!(new = ft_memalloc(sizeof(t_room))))
		ft_error(graph, 2);
	return (new);
}

void			add_room(char *room_name, t_room **new, t_graph *graph) 
{
	int			i;

	i = graph->room_count;
	*new = create_room(graph);

	graph->adlist[i] = *new;
	graph->adlist[i]->name = room_name;
	//printf("room |%d|%d\n", graph->start, graph->end);
	if (graph->start == 1)
	{
		graph->adlist[i]->s = 1;
		graph->start++;
	}
	if (graph->end == 1)
	{
		graph->adlist[i]->e = 1;
		graph->end++;
	}
	//graph->adlist[i]->s = (graph->start == 1) ? 1 && graph->start++ : 0;
	//graph->adlist[i]->e = (graph->end == 1) ? 1 && graph->end++ : 0;
	graph->room_count++;
}

t_graph*		create_graph(int rooms) 
{
	t_graph		*new;

	new = ft_memalloc(sizeof(t_graph));
	new->adlist = ft_memalloc(sizeof(t_room*) * rooms);
	return (new);
}

//should it exit when 0 ants?
void				ft_ants_num(char *line, t_graph* data)
{
	if (!(ft_strisdigit(line)))
		ft_error(data, 2); //check
	data->ants = ft_atoi(line);
}

int				link_rooms(char *room, int i, t_graph* data)
{
	t_room	*new;
	t_room	*tmp;

	new = create_room(data);
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

// t_queue	*create_queue(int size, t_queue *new)
// {
// 	t_queue	*tmp;
// 	t_queue	*head;
// 	new = ft_memalloc(sizeof(t_queue));
// 	head = new;
// 	while (size--)
// 	{
// 		tmp = ft_memalloc(sizeof(t_queue));
// 		//new->index = 1;
// 		new->next = tmp;
// 		new = new->next;
// 	}
// //	printf("new->index %d\n", head->index);
// 	return (head);
// }

// Adding elements into queue
// void			add_to_queue(t_queue *q, t_room	*room)
// {
// 	q->name = room->name;
// 	if (room->next) // && not in queue already
// 	{
// 		//
// 		while (room->next)
// 		{
// 			q = q->next;
// 			room = room->next;
// 			q->name = room->name;
// 		}
// 	}
// //	printf("q->i %d\n", q->i);
// }

// void			print_queue(t_queue *q, int i)
// {
// 	while (q->next)
// 	{
// 		printf("queue note number %d q->name %s\n", i, q->name);
// 		q = q->next;
// 		i++;
// 	}
// }

// void			remove_from_queue(t_queue *q, int room_number)
// {
// 	q->index = q->index;
// 	//remove link from linked list
// }

// int				queue_is_empty(t_queue *q)
// {
// 	if (q->next == NULL)
// 		return (1);
// 	return (0);
// }

int				find_index_name_room(t_graph* data, char *s)
{
	int		i;

	i = 0;
	while (data->adlist[i])
	{
		if (!(ft_strcmp(data->adlist[i]->name, s)))
			return (i);
		i++;
	}
	return(ft_error(data, 1));
}

// int				bfs(t_graph* data, int start_i)
// {
// 	t_queue		*q;
// 	t_room		*tmp;

// 	q = create_queue(data->room_count, data->q);
// 	print_queue(q, 0);
// 	tmp = data->adlist[start_i];
// 	tmp->visited = 1;
	
// 	// while didn't reach all nodes
// 		add_to_queue(q, tmp);
// 	print_queue(q, 0);
	
// 	// while (!queue_is_empty)
// 	// {
// 	// 	start_i = find_index_name_room(data, tmp->name);
// 	// 	printf("index of room %d\n", start_i);
// 	// 	add_to_queue(q, start_i);
// 	// 	tmp = tmp->next;
// 	// }
// 	return (1);
// }

int				ft_link(char *line, t_graph* data)
{
	int		i;
	int		flag;
	char	**room;

	i = 0;
	flag = 0;
	room = ft_strsplit(line, '-'); 
	//0-2 nana-lala nana = 1 ADD INDEX to notes
	while (data->adlist[i] && i < data->room_count)
	{
		//printf("loop %d|%d |%s\n", len, i, data->adlist[i]->name);
		if (!(ft_strcmp(data->adlist[i]->name, room[0])))
			flag += link_rooms(room[1], i, data);
		if (!(ft_strcmp(data->adlist[i]->name, room[1])))
			flag += link_rooms(room[0], i, data);
		i++;
	}
	return (flag == 2 ? 1 : ft_error(data, 5));
}

int				ft_room(char *line)
{
	char	**room;
	t_graph	*new;

	new = NULL; // delete
	if (line[0] == 'L') 
		ft_error(new, 4);
	// if (!(ft_strchr(line, '-')) || !(ft_strchr(line, '#')))
	// 	return (0);
	room = ft_strsplit(line, ' ');
	if (!room[0] || room[3] || !ft_strisdigit(room[1]) || !ft_strisdigit(room[2]))
		ft_error(new, 5);
	//add_room(room[0], &new ,data);
	//ft_printf("%s\n", line);
	return (1);
}

int				ft_comment(char *line, t_graph* data)
{
	// if (!data->ants) // ants if 0
	// 	ft_error(data, 1);
	if (!(ft_strcmp(line, "##start")))
		data->start++;
	else if (!(ft_strcmp(line, "##end")))
		data->end++;
	//ft_printf("%s\n", data->line);
	return (0);
}

int				ft_error(t_graph* data, int opt)
{
	free(data);

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
	exit(0);
}

// t_graph*		parse_graph(char **av, t_graph* graph) 
// {
// 	int			i;
// 	i = 0;
// 	av[1] = NULL; // delete
// 	if (!(graph = create_graph(4))) // diffferent order, graph shall be created after input is read
// 		ft_error(graph, 2);
// 	if (ft_ants_num(graph))
// 		ft_printf("%d\n", graph->ants);
// 	while (get_next_line(0, &graph->line) == 1)
// 	{
// 		if (graph->line[0] == '#')
// 			ft_comment(graph);
// 		else if (ft_strchr(graph->line, ' ') && !(ft_strchr(graph->line, '-')) && !(ft_strchr(graph->line, '#')))
// 			ft_room(graph);
// 		else if (ft_strchr(graph->line, '-') && ft_link(graph))
// 			ft_printf("%s\n", graph->line);
// 		else
// 			ft_error(graph, 1);
// 		free(graph->line);
// 		graph->line = NULL;
// 	}
// 	ft_printf("\n");
// 	print_rooms(graph);
// 	bfs(graph, 1);
// 	return (0);
// }


char			**parse_input(char **av) 
{
	int		i;
	char	**line;
	int		room;

	i = 0;
	room = 0;
	av[0] = NULL; // delete if av not needed
	line = ft_memalloc(sizeof(char*) * 100); // if goes to 101 malloc more
	while (get_next_line(0, &line[i]) == 1)
	{
		i++;
	}
	return (line);
}

t_graph*		parse_graph(char **line, t_graph* graph) 
{
	int		i;

	i = 0;

	ft_ants_num(line[0], graph);
	while (line[i])
	{
		ft_printf("%s\n", line[i]);
		if (line[i][0] == '#')
			ft_comment(line[i], graph);
		// else if 
		// 	ft_room(line[i], graph);
		else if (ft_strchr(line[i], '-'))
			ft_link(line[i], graph);
		// else
		// 	ft_error(graph, 1);
		i++;
	}
	ft_printf("\n");
	//print_rooms(graph);
	//bfs(graph, 1);

	// delete below if printing not needed
	// i = 0;
	// while (line[i])
	// {
	// 	ft_printf("%s\n", line[i]);
	// 	i++;
	// }
	return (graph); // change
}

int				count_rooms(char **line)
{
	int i;
	int		room;

	i = 0;
	room = 0;
	while (line[i])
	{
		if (ft_strchr(line[i], ' ') && ft_room(line[i]))
			room++;
		i++;
	}
	return (room);
}

int				main(int argc, char **argv)
{
	t_graph*	data;
	char		**line;

	if (argc < 1)
		return (0);
	line = parse_input(argv);
	data = create_graph(count_rooms(line));
	parse_graph(line, data);
}