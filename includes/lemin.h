/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/04 11:26:34 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

#include <stdio.h> // test
#include <stdlib.h>
#include "../libft/libft.h"

#define SIZE 400

typedef struct s_room
{
	char	*name;
	int		index;
	int		prev_room_index;
	int		s;
	int		e;
	int		visited;
	struct s_room	*next;
} t_room;

typedef	struct	s_queue
{
	t_room	*head;
	t_room	*tail;
}				t_queue;


typedef struct s_graph
{
	int		ants;
	int		room_total;
	char	*room_name;
	int		*queue;

	t_room	**adlist;
}				t_graph;

int		ft_error(int opt);

void	print_rooms(t_graph* graph);

int		ft_strisdigit(char *s);

#endif
