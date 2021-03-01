/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/03/02 00:02:17 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	paths_count(t_path **path)
{
	int		i;

	i = 0;
	while (path[i])
		i++;
	//ft_printf("total len of all paths: %d\n: ", i);
	return (i);
}


/*
** If path lenght plus number of ants in room more then
** ant_count move to next room
** If path lenght plus number of ants in room less or equal then
** add ants to current room
*/

void			move_ants(t_path *path, t_graph *graph)
{
	t_path *temp;
//	t_room *room;

	temp = path->next;
//	room = graph->adlist[temp->i];

	ft_printf("L%d-%s ", path->id, graph->adlist[temp->i]->name);

	if (!temp->next)
		return;

	//put ant to next room in adlist
	temp = temp->next;
		if (!graph->adlist[temp->i]->visited)
		{
			graph->adlist[temp->i]->ant_id = path->id;
			graph->adlist[temp->i]->prev_room_index = temp->i;
		//	ft_printf("one L%d-%s \n", graph->adlist[temp->i]->ant_id, graph->adlist[temp->i]->name);
			graph->adlist[temp->i]->visited = 1;
			graph->adlist[temp->i]->fresh = 1;
		}


		// 	ft_printf("next L%d-%s \n", path->id, graph->adlist[temp->next->i]->name);
//	ft_printf("\n occupied L%d-%s \n", path->ant_id, graph->adlist[temp->i]->name);
}

static void		ant_in_rooms_out(t_path **path, t_graph *graph)
{
	t_path *temp;
	int i;
	int id;
	char *name;

	i = -1;
	while (path[++i])
	{
		temp = path[i]->next;
		while (temp->next)
		{
			temp = temp->next;
			if (graph->adlist[temp->i]->visited  && graph->adlist[temp->i]->fresh)
			{
				graph->adlist[temp->i]->fresh = 0;
				break;
			}
			if (graph->adlist[temp->i]->visited  && !graph->adlist[temp->i]->fresh) //if ant in room print out
			{
				id = graph->adlist[temp->i]->ant_id;
				name = graph->adlist[graph->adlist[temp->i]->prev_room_index]->name;
				ft_printf("L%d-%s ", id, name);
				graph->adlist[temp->i]->visited = 0;
			}
		}
	}
	ft_printf("\n");
}

void	ant_start(int ant_count, t_path **path, t_graph *graph)
{

	int		i;
	int		j;

	j = 0;
	ant_count = graph->ants;
	i = 1;
	while (ant_count)
	{
		j = 0;
		while (path[j])
		{
			if (path[j]->ants_wait_list) // while there are ants awaiting
			{
				path[j]->id = i;
				move_ants(path[j], graph); //sending one to path
				path[j]->ants_wait_list--;
				i++;
			}
			j++;
		}
		ant_in_rooms_out(path, graph);
	//	ft_printf("\n");
		ant_count--;
	}

}

int		*allocate_ants_to_rooms(t_path **path, t_graph *graph)
{
	int		i;
	int		j;
	int		ant_count;
	int		path_total;

	i = 0;
	j = -1;
	path_total = paths_count(path);
	//  if not malloc, error
//	ft_printf("path_total %d\n",path_total );
	ant_count = graph->ants;

	while (ant_count > 0)
	{
		i = 0;
		//ft_printf("loop %d\n", ant_count );
		while (ant_count < path[i]->len && path_total > 1)
		{
			path_total--;
		}
		//ft_printf("loop path_total %d\n", path_total );
		while (i < path_total)
			path[i++]->ants_wait_list++;
		ant_count -= path_total;
	}
	//test
	print_paths(path);
	j = -1;
	while (++j < i)
	{
		ft_dprintf(fd, "path distributed %s %d|%d\n",  graph->adlist[path[j]->i]->name, path[j]->ants_wait_list, path[j]->len);
	}
	//test

	ant_start(graph->ants, path, graph);

	return (NULL); //change
}
