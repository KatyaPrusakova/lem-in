/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/07 12:00:22 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

#include <stdio.h> // test
#include <stdlib.h>
#include "../libft/libft.h"

#define SIZE 400

typedef struct		s_room
{
	char			*name;
	int				index;
	int				prev_room_index;
	int				s;
	int				e;
	int				visited;
	struct s_room	*next;
}					t_room;

typedef	struct		s_queue
{
	t_room			*head;
	t_room			*tail;
}					t_queue;

typedef struct		s_graph
{
	int				ants;
	int				room_total;
	char			*room_name;
	t_room			**adlist;
	t_queue			*q;
}					t_graph;

/*
** The paths are saved as linked lists using t_path stuct pointers.
*/

typedef	struct 		s_path
{
	int				i;
	int				len;
	struct s_path	*next;
}					t_path;


/*
** LEMIN.C
*/


/*
** MALLOC_FREE.C
*/

t_graph*			create_graph(int rooms);

/*
** PARSE_INPUT.C
*/

char				**parse_input(char **av);

/*
** PARSE_LINK.C
*/

int					is_link(char *line, t_graph* data);
int					link_rooms(char *room, int i, t_graph* data);
void				add_index_to_room(t_graph* data, char *name, int index, int i);
void				parse_link(int i, char **line, t_graph* graph);

/*
** PARSE_ROOM.C
*/

int					count_rooms(char **line);
int					parse_room(char **line, t_graph* graph);
void				add_room(int flag, char *room_name, t_graph *graph);
char*				is_room(char *line);

/*
** PARSE_ANTS.C
*/

void				parse_ants(char *line, t_graph* data);

/*
** PRINT_OUT.C
*/

void				print_rooms(t_graph* graph);
int					print_error(int opt);



//add to libft
int					ft_strisdigit(char *s);
char				*ft_firstword(char **line, int i);


//draft
// int					bfs(t_graph* data);
t_path				**bfs(int max_paths, t_graph *graph, t_room	*room);
int					queue_is_empty(t_queue *q);
void				remove_from_queue(t_queue *q, int room_number);
void				add_to_queue(t_queue *q, t_room	*room);
t_queue				*create_queue(int size, t_queue *new);

//queue functions

t_queue		*enqueue(int index, t_queue *q, t_room **adlist, int prev);
t_queue		*dequeue(t_queue *q);

/*
** path finding
*/

int		**find_paths(t_graph *graph);

#endif
