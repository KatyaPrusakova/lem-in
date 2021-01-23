/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/23 19:21:54 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_rooms(t_graph* graph)
{
	int i;
	t_room	*tmp;

	i = 0;
	while (graph->adlist[i])
	{
		printf("%d |%s|", i, graph->adlist[i]->name);
		if (graph->adlist[i]->next != NULL)
		{
			tmp = graph->adlist[i];
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
				printf(" -> |%s|", tmp->name);
			}
		}
		printf("\n");
		i++;
	}
}

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
	graph->room_count++;
}

t_graph*		create_graph(int rooms) 
{
	t_graph		*new;

	new = ft_memalloc(sizeof(t_graph));
	new->adlist = ft_memalloc(sizeof(t_room*) * rooms);
	return (new);
}

int				ft_strisdigit(char *s)
{
	int i;
	int l;

	i = 0;
	l = ft_strlen(s);
	if (!s || l == 0)
		return (0);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return(l == i ? 1 : 0);
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

int				link_rooms(char *one, char *two, int i, t_graph* data)
{
	t_room	*new;
	t_room	*tmp;

	new = create_room(data);
	printf("connect %s-%s addlist %s\n", one, two, data->adlist[i]->name);
	tmp = data->adlist[i];
	if (tmp->next)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	tmp->next = new;
	new->name = two;
	return (0);
}

int				ft_link(t_graph* data)
{
	int		i;
	char	**room;

	//check that both names exists in graph->adlist
	i = 0;
	room = ft_strsplit(data->line, '-');
	while (data->adlist[i] && i < data->room_count)
	{
		//printf("loop %d|%d |%s\n", len, i, data->adlist[i]->name);
		if (!(ft_strcmp(data->adlist[i]->name, room[0])))
			link_rooms(room[0], room[1], i, data);
		if (!(ft_strcmp(data->adlist[i]->name, room[1])))
			link_rooms(room[1], room[0], i, data);
		i++;
	}
	//printf("same %s-%s\n", room[1], data->adlist[i]->next->name);
	return (0);
}

int			ft_room(t_graph* data)
{
	char	**room;
	t_room	*new;

	if (data->line[0] == 'L') 
		ft_error(data, 4);
	room = ft_strsplit(data->line, ' ');
	if (!room[0] || room[3] || !ft_strisdigit(room[1]) || !ft_strisdigit(room[2]))
		ft_error(data, 5);
	add_room(room[0], &new ,data);

	//printf("room |%s|%s|%s\n", room[0], room[1], room[2]);
	return (0);
}

int			ft_comment(t_graph* data)
{
	//printf("comment %s\n", data->line);
	if (!data->ants) // ants if 0
		ft_error(data, 1);
	if (!(ft_strcmp(data->line, "##start")))
		data->start++;
	else if (!(ft_strcmp(data->line, "##end")))
		data->end++;
	//printf("end %d it |%d %d|\n", data->ants, data->end, data->start);

	return (0);
}

int			ft_error(t_graph* data, int opt)
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

t_graph*	parse_graph(char **av, t_graph* graph) 
{
	
	int		i;

	i = 0;
	if (!(graph = create_graph(4)))
		ft_error(graph, 2);
	ft_ants_num(graph);
	printf("start %d now |%s|\n", graph->ants, av[1]);
	while (get_next_line(0, &graph->line) == 1)
	{
		if (graph->line[0] == '#')
			ft_comment(graph);
		else if (ft_strchr(graph->line, ' ') && !(ft_strchr(graph->line, '-')) && !(ft_strchr(graph->line, '#')))
			ft_room(graph);
		else if (ft_strchr(graph->line, '-'))
			ft_link(graph);
		else
			ft_error(graph, 0);
		free(graph->line);
		graph->line = NULL;
	}
	print_rooms(graph);
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