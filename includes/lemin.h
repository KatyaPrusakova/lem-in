/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/23 19:07:42 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

#include <stdio.h> // test
#include <stdlib.h>
#include "../libft/libft.h"

#define BUFF 4000

typedef struct s_room
{
	char	*name;
	int		s;
	int		e;
	struct s_room	*next;
} t_room;

typedef struct s_graph 
{
	int		ants;
	int		start;
	int		end;
	int		room_count;
	char	*room_name;
	char	*line;
	t_room	**adlist;
} t_graph;

int		ft_error(t_graph* data, int opt);
void	print_rooms(t_graph* graph);

#endif