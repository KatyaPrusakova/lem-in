/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/25 21:53:42 by eprusako         ###   ########.fr       */
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

// typedef struct s_queue {
// 	int		index;
// 	char	*name;
// 	struct s_queue	*next;
// } t_queue;



typedef struct s_graph 
{
	int		ants;
	int		start; // bad idea, change start to 0 note
	int		end;
	int		room_count;
	char	*room_name;
	int		*queue;
	char	*line;
	t_room	**adlist;
} t_graph;

int		ft_error(t_graph* data, int opt);

void	print_rooms(t_graph* graph);

int		ft_strisdigit(char *s);

#endif