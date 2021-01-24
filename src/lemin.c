/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/24 19:05:06 by eprusako         ###   ########.fr       */
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
int				ft_ants_num(t_graph* data)
{
	get_next_line(0, &data->line);
	if (!(ft_strisdigit(data->line)))
		return (0);
	data->ants = ft_atoi(data->line);
	data->ants < 0 ? ft_error(data, 3) : free(data->line);
	return (1);
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

t_queue	*create_queue(int size, t_queue *new)
{
	new = ft_memalloc(sizeof(t_queue));
	new->waiting_list = ft_memalloc(sizeof(size));
	return (new);
}

// int			sort_graph(t_graph* data)
// {
// 	t_room	*tmp;
// 	int		head;
// 	int		end;
// 	while (graph->adlist[i])
// 	{
// 		if (data->adlist[i]->s && i != 0)
// 			{
// 				tmp = data->adlist[i];			
// 			}
// 		if (tmp->next)
// 		{
// 			while (tmp->next != NULL)
// 				tmp = tmp->next;
// 		}
// 	}
// }

// Adding elements into queue
void			add_to_queue(t_queue *q, int room_number)
{
	int i;

	i = 0;
	q->waiting_list[q->i] = room_number;
	while (q->waiting_list[i]) //delete
	{
		printf("queue is %d\n", q->waiting_list[i]);
		i++;
	}
	q->i++;
}

void			remove_from_queue(t_queue *q, int room_number)
{
	q->waiting_list[room_number] = NULL;
}

int			queue_is_empty(t_queue *q)
{
	if (q->waiting_list)
		return (1);
	return (0);
}

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

int				bfs(t_graph* data, int start_i)
{
	t_queue		*q;
	t_room		*tmp;

	q = create_queue(data->room_count, data->q);
	data->adlist[start_i]->visited = 1;
	tmp = data->adlist[start_i];

	add_to_queue(q, start_i);
	while (!queue_is_empty(q))
	{
		start_i = find_index_name_room(data, tmp->name);
		printf("index of room %d\n", start_i);
		add_to_queue(q, start_i);
		tmp = tmp->next;
	}
	return (1);
}

int				ft_link(t_graph* data)
{
	int		i;
	int		flag;
	char	**room;

	i = 0;
	flag = 0;
	room = ft_strsplit(data->line, '-');
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

int				ft_room(t_graph* data)
{
	char	**room;
	t_room	*new;

	if (data->line[0] == 'L') 
		ft_error(data, 4);
	room = ft_strsplit(data->line, ' ');
	if (!room[0] || room[3] || !ft_strisdigit(room[1]) || !ft_strisdigit(room[2]))
		ft_error(data, 5);
	add_room(room[0], &new ,data);
	ft_printf("%s\n", data->line); //
	return (0);
}

int				ft_comment(t_graph* data)
{
	if (!data->ants) // ants if 0
		ft_error(data, 1);
	if (!(ft_strcmp(data->line, "##start")))
		data->start++;
	else if (!(ft_strcmp(data->line, "##end")))
		data->end++;
	ft_printf("%s\n", data->line);
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
		write(1, "link is wrong\n", 22);
	exit(0);
}

t_graph*		parse_graph(char **av, t_graph* graph) 
{
	
	int			i;

	i = 0;
	av[1] = NULL; // delete
	if (!(graph = create_graph(4)))
		ft_error(graph, 2);
	if (ft_ants_num(graph))
		ft_printf("%d\n", graph->ants);
	while (get_next_line(0, &graph->line) == 1)
	{
		if (graph->line[0] == '#')
			ft_comment(graph);
		else if (ft_strchr(graph->line, ' ') && !(ft_strchr(graph->line, '-')) && !(ft_strchr(graph->line, '#')))
			ft_room(graph);
		else if (ft_strchr(graph->line, '-') && ft_link(graph))
			ft_printf("%s\n", graph->line);
		else
			ft_error(graph, 1);
		free(graph->line);
		graph->line = NULL;
	}
	ft_printf("\n");
	print_rooms(graph);
	bfs(graph, 1);
	return (0);
}

int main(int argc, char **argv)
{
	t_graph* data;

	data = NULL;
	if (argc < 1)
		return (0);
	parse_graph(argv, data);
}