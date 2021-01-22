/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/22 13:14:37 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// t_room* create_room( t_graph *, int a, int b) 
// {
	
// }

t_graph* create_graph(int rooms) 
{
	t_graph* new;

	new = ft_memalloc(sizeof(t_graph));
	new->room_count = rooms;
	new->adlist = ft_memalloc(sizeof(t_room*) * rooms);
	return (new);
}

int		ft_islink(t_graph* data)
{
	if (ft_strchr(data->line, '-'))
		return (1);
	return (0);
}

int		ft_isroom(t_graph* data)
{
	if (ft_strchr(data->line, ' ') && ft_isdigit(data->line[0]))
		return (1);
	return (0);
}

int		ft_iscomment(t_graph* data)
{
	int i;

	i = 0;
	if ( !data->ants)
		error_output(data, 1);
	if (ft_strstr(data->line, "##start"))
		data->start++;
	else if (ft_strstr(data->line, "##end"))
		data->end++;
	return (0);
}

int		error_output(t_graph* data, int opt)
{
	free(data);

	if (opt == 0)
		exit(0);
	if (opt == 1)
		exit(0);
	exit(0);
}

t_graph* parse_graph(char **av, t_graph* graph) 
{
	
	int		i;

	i = 0;
	av = 0;
	//read input
	get_next_line(0, &graph->line);
	graph->ants = ft_atoi(graph->line);
	free(graph->line);

	while (get_next_line(0, &graph->line) > 1)
	{
		if (graph->line[0] == '#')
			ft_iscomment(graph);
		else if (ft_strchr(graph->line, ' ') && !(ft_strchr(graph->line, '-')) && !(ft_strchr(graph->line, '#')))
			ft_isroom(graph);
		else if (ft_strchr(graph->line, '-'))
			ft_islink(graph);
		else
			error_output(graph, 0);
		free(graph->line);
	}
	return (0);
//	if (ft_islink(line))
			
	// create_graph();
}

int main(int argc, char **argv)
{
	t_graph* data;

	data = NULL;
	if (argc < 1)
		return (0);
	parse_graph(argv, data);
}