/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/22 16:19:12 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// t_room* create_room( t_graph *, int a, int b) 
// {
	
// }

t_graph* create_graph(int rooms) 
{
	t_graph *new;

	new = ft_memalloc(sizeof(t_graph));
	new->adlist = ft_memalloc(sizeof(t_room*) * rooms);
	return (new);
}

int		ft_link(t_graph* data)
{
	printf("link %s\n", data->line);
	if (ft_strchr(data->line, '-'))
		return (1);
	return (0);
}

int		ft_room(t_graph* data)
{
	printf("room %s\n", data->line);
	if (ft_strchr(data->line, ' ') && ft_isdigit(data->line[0]))
		return (1);
	return (0);
}

int		ft_comment(t_graph* data)
{
	int i;

	i = 0;
	printf("comment %s\n", data->line);
	if (!data->ants)
		ft_error(data, 1);
	if (ft_strstr(data->line, "##start"))
		data->start++;
	else if (ft_strstr(data->line, "##end"))
		data->end++;
	printf("end %d it |%d %d|\n", data->ants, data->end, data->start);

	return (0);
}

int		ft_error(t_graph* data, int opt)
{
	free(data);

	if (opt == 0)
		exit(0);
	if (opt == 1)
		write(1, "run away\n", 10);
	if (opt == 2)
		write(1, "malloc failed\n", 15);
	exit(0);
}

t_graph* parse_graph(char **av, t_graph* graph) 
{
	
	int		i;

	i = 0;
	//read input
	if (!(graph = create_graph(4)))
		ft_error(graph, 2);
	get_next_line(0, &graph->line);
	graph->ants = ft_atoi(graph->line);
	free(graph->line);
	printf("start %d now |%s|\n", graph->ants, av[1]);
	while (get_next_line(0, &graph->line) == 1)
	{
		printf("loop %s\n", graph->line);
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
	return (0);
//	if (ft_islink(line))
			
}

int main(int argc, char **argv)
{
	t_graph* data;

	data = NULL;
	if (argc < 1)
		return (0);
	parse_graph(argv, data);
}