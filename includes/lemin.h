/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/06/21 19:30:49 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h> //delete
# include <fcntl.h> //delete?
# include <stdlib.h>
# include "../libft/libft.h"

# define START "##start"
# define END "##end"
# define MAX_ANTS "100000"

int fd; //delete

typedef struct		s_room
{
	char			*name;
	int				index;
	int				prev_room_index;
	int				out;
	int				visited;
	int				antnbr;
	struct s_room	*next;
}					t_room;

typedef	struct		s_search
{
	struct s_queue	*q;
	struct s_room	*tmp;
	struct s_room	*room;
	struct s_path	*path;
	struct s_path	**set;
	int				*visited;
	int				path_no;
	int				start;
	int				end;
}					t_search;

typedef	struct		s_queue
{
	t_room			*head;
	t_room			*tail;
}					t_queue;

typedef struct		s_graph
{
	int				ants;
	int				unlimited_flow;
	int				visualize;
	int				room_total;
	int				max_paths;
	char			*room_name;
	int				**weight_m;
	t_room			**adlist;
	t_queue			*q;
}					t_graph;

/*
** The paths are saved as linked lists using t_path stuct pointers.
*/

typedef	struct		s_path
{
	int				i;
	int				len;
	int				ant;
	char			*name;
	t_room			*room;
	struct s_path	*next;
}					t_path;

/*
** BFS.C
*/

int					check_flow(t_room *src, t_room *dst, int max_flow, \
t_graph *g);
void				visit_room(t_search s, t_graph *graph, int max_flow);
t_path				*bfs(t_graph *g, int start, int end);
t_search			init_search(t_graph *g, int start, int end);
t_path				**bfs_set(t_graph *graph, int start, int end);

/*
** CREATE_GRAPH.C
*/

t_graph				*create_graph(int rooms, char **line);

/*
** CREATE_QUEUE.C
*/

void				free_queue(t_queue *q);
int					is_queued(int index, t_queue *q);
t_queue				*enqueue(int index, t_queue *q, t_room **adlist, int prev);
t_queue				*dequeue(t_queue *q);

/*
** EDGE_WEIGTH.C
*/

int					check_weight(int link_weight, int set_weight);
void				mod_edgeweight_path(t_graph *g, t_path *path);

/*
** LEMIN.C
*/

t_graph				*lem_in(t_graph *g, char **input);

/*
** LINK_EXISTS.C
*/

int					link_exists(t_graph *g, int a, int b);

/*
** MALLOC_FREE.C
*/

void				free_data(t_graph *data, char **input);
int					**create_matrix(int height, int width);
t_path				*free_path(t_path *path);
t_path				**free_path_set(t_path ***set);
void				free_adlist(t_room **graph, size_t size);

/*
** MOVE_ANTS.C
*/

void				move_all_to_end(int ant_amount, char *end_room);
int					push_path(t_path *p, int add_ant);
void				empty_paths(t_path **p);
int					pathlen_is_optimal(t_path **p, int path_nbr, int ants_left);
void				move_ants(t_path **p, t_graph *g);

/*
** PARSE_ANTS.C
*/

int					is_comment(char **str, int i);
int					parse_ants(char **line, t_graph *data);
int					valid_ants(int flag, char **line);

/*
** PARSE_INPUT.C
*/

char				**input_realloc(char **input, int len);
void				valid_map(char **input);
char				**parse_input(void);

/*
** PARSE_LINK.C
*/

int					link_to_adlist(int a, int b, t_graph *g);
int					create_edge(int *index, t_graph *data);
int					*edge_index(int link_name, int i, char **room, t_graph *graph);
void				create_room_capacity(t_graph *g);
int					parse_links(int i, char **input, t_graph *g);

/*
** PARSE_ROOM.C
*/

int					count_rooms(char **line);
void				add_room(int flag, char *room_name, t_graph *graph);
int					parse_room(int i, char **line, t_graph *graph);
int					is_room(char **input, int i);

/*
** PATH_CALCULATIONS.C
*/

int					count_max_paths(t_graph *graph);
int					paths_in_array(t_path **set);
int					set_rooms_total(t_path **set, int last_room);
int					path_cmp(t_path *p1, t_path *p2);

/*
** PATH_FINDING.C
*/

int					count_moves(t_path **path, int ants);
t_path				**set_cmp(t_path **p1, t_path **p2, int ants);
t_path				**clean_set(t_path **set, t_graph *g);
t_path				**edmonds_karp(t_graph *g);
t_path				**unlimited_flow(void);

/*
** PRINT_OUT.C
*/

void				print_rooms(t_graph *graph);
int					print_error(int opt, char **line);
void				print_input(char **line);
void				print_matrix(int **matrix, int size);
void				print_paths(t_path **path, t_room **adlist);

/*
** SAVE_PATH.c
*/

void				*delete_room_in_path(t_path *p, int index);
void				clean_path(t_path *p, t_graph *g);
t_path				*add_room_to_path(t_path *head, char *name, int index);
t_path				*save_path(int *visited, t_graph *g, t_search s, \
int prev_room);
int					check_path(t_graph *graph, t_search s, int *path_no, \
int prev_room);

/*
** VISUALIZE.C
*/

void				visualizer_clean_graph(int visualize);
void				path_to_visualizer(t_path *p, int offset, int mod_flow);
void				visualize_search(t_graph *g, t_room *room, int **matrix);

/*
** //   add to libft
*/

int					ft_strisdigit(char *s);
char				*first_word(char **line, int i);

#endif
