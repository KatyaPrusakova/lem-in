/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/04 22:15:29 by eprusako         ###   ########.fr       */
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

typedef struct s_graph 
{
	int		ants;
	int		room_total;
	char	*room_name;
	t_room	**adlist;
} t_graph;

/*
** MALLOC_FREE.C
*/

t_graph*		create_graph(int rooms);

int				ft_error(int opt);

/*
** PRINT_OUT.C
*/

void	print_rooms(t_graph* graph);

int		ft_strisdigit(char *s);

#endif