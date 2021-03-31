/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/03/31 15:51:10 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEMIN_H
#define LEMIN_H

#include <stdio.h> // test
#include <fcntl.h> //test
#include <stdlib.h>
#include "../libft/libft.h"

#define SIZE 400 //is it used anywhere?

#define START	"##start"
#define END		"##end"

int fd; //test
int	fd_zero; //test. Use argv instead of stdin.

typedef struct		s_room
{
	char			*name;
	int				index;
	int				prev_room_index;
	int				end;
	int				visited;
	int				antnbr;
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
	int				ants_end;
	int				visualize;
	int				room_total;
	char			*room_name;
	int				**weight;
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
	int				ants_wait_list; //added
	t_room			*room;
	struct s_path	*end;
	struct s_path	*prev;
	struct s_path	*next;
}					t_path;

/*
** Create weight matrix
*/

int **create_matrix(int height, int width);

/*
** LEMIN.C
*/

/*
** EDGE_WEIGTH.C
*/

int		**mod_edge_weight(int **matrix, t_path *path);
int		check_weight(int link_weight, int set_weight);


/*
** MALLOC_FREE.C
*/

t_graph*			create_graph(int rooms);
t_path*				free_path(t_path *path);


/*
** PARSE_INPUT.C
*/

char				**parse_input(void);

/*
** PARSE_LINK.C
*/

int					is_link(char **room, int *index, t_graph* data);
int					link_rooms(char *room, int i, t_graph* data);
void				add_index_to_room(t_graph* data, char *name, int index, int i);
int					parse_link(int i, char **line, t_graph* graph);

/*
** PARSE_ROOM.C
*/

int					count_rooms(char **line);
int					parse_room(int i, char **line, t_graph* graph);
int					add_room(int flag, char *room_name, t_graph *graph);
char*				is_room(char **input, int i);

/*
** PARSE_ANTS.C
*/

int				parse_ants(char **line, t_graph* data);
int				valid_ants(int flag, char **line);
/*
** PRINT_OUT.C
*/

void				print_rooms(t_graph* graph);
int					print_error(int opt, char **line);
void				print_input(char **line);

//add to libft
int					ft_strisdigit(char *s);
char				*ft_firstword(char **line, int i);


//draft

t_path				*bfs(int max_paths, t_graph *graph, int set_weight);
t_path				**bfs_3(int max_paths, t_graph *graph, t_room	*room);


//queue functions

t_queue				*enqueue(int index, t_queue *q, t_room **adlist, int prev);
t_queue				*dequeue(t_queue *q);

/*
** path finding
*/

t_path				**find_paths(t_graph *graph);
void				print_paths(t_path **path);

/*
** path_calculations.c
*/

int					count_max_paths(t_graph *graph);
int					calculate_set_len(t_path **set);
int					paths_in_array(t_path **set);


/*
** save_path.c
*/

t_path		**check_path(t_graph *graph, int *visited, int find_path, t_path **path, int *path_no);
t_path		*save_path(int *visited, int find_path, /*int **matrix,*/int end_room);
int			**mod_edge_weight(int **matrix, t_path *path);



/*
** visualize.c
*/

void				queue_to_visualizer(t_room **adlist, t_queue *q, int visualize); //testing
void				visited_to_visualizer(int current_index, int visited_from, int visualize);

/*
** ANTS_FLOW.C
*/

int					*allocate_ants_to_rooms(t_path **path, t_graph *graph);

//test

void	print_matrix(int **matrix, int size);


#endif
