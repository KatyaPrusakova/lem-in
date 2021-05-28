/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/05/28 14:07:22 by ksuomala         ###   ########.fr       */
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

typedef	struct 		s_path
{
	int				i;
	int				len;
	int				ant;
	char			*name;
	t_room			*room;
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

int					check_weight(int link_weight, int set_weight);

/*
** MALLOC_FREE.C
*/

t_graph*			create_graph(int rooms, char **line);
void				free_adlist(t_room **graph, size_t size);
t_path*				free_path(t_path *path);
t_path**			free_path_set(t_path ***set);
void				free_data(t_graph *data, char **input);

/*
** PARSE_INPUT.C
*/

char				**parse_input(void);

/*
** PARSE_LINK.C
*/

int					create_edge(int *index, t_graph* data);
int					link_rooms(int a, int b, t_graph *g);
void				add_index_to_edge(t_graph* data, char *name, int index, int i);
// int					parse_link(int i, char **line, t_graph* graph);
int					parse_links(int i, char **input, t_graph *g);


/*
** PARSE_ROOM.C
*/

int					count_rooms(char **line);
int					parse_room(int i, char **line, t_graph* graph);
void				add_room(int flag, char *room_name, t_graph *graph);
int					is_room(char **input, int i);

/*
** PARSE_ANTS.C
*/

int					parse_ants(char **line, t_graph* data);
int					valid_ants(int flag, char **line);
/*
** PRINT_OUT.C
*/

void				print_rooms(t_graph* graph);
int					print_error(int opt, char **line);
void				print_input(char **line);

//add to libft
int					ft_strisdigit(char *s);
char				*first_word(char **line, int i);

//draft

t_path				*bfs(t_graph *g, int start, int end);
t_search			init_search(t_graph *g, int start, int end);
t_path				**bfs_set(t_graph *graph, int start, int end);

int					end_is_neighbour(t_room *head, int end);
t_path 				**unlimited_flow(void);
t_path				**edmonds(t_graph *g);
void				clean_path(t_path *p, t_graph *g);

//DFS

t_path				**edmonds_karp(t_graph *g);

//queue functions

t_queue			*enqueue(int index, t_queue *q, t_room **adlist, int prev);
t_queue			*dequeue(t_queue *q);
int				is_queued(int index, t_queue *q);
void			free_queue(t_queue *q);

/*
** path finding
*/

t_path			**find_paths(t_graph *graph);
t_path			**find_sets(t_graph *graph);
void			print_paths(t_path **path, t_room **adlist);

/*
** path_calculations.c
*/

int				count_max_paths(t_graph *graph);
int				set_rooms_total(t_path **set, int last_room);
int				paths_in_array(t_path **set);
int				path_cmp(t_path *p1, t_path *p2);


/*
** sort_adlist.c
*/

t_room			*adlist_mergesort(t_room *head, int start, int **weight_matrix);
void			sort_adlist_array(t_graph *g);

/*
** save_path.c
*/

int				check_path(t_graph *graph, t_search s, int *path_no, int prev_room);
t_path			*save_path(int *visited, t_graph *g, t_search s, int prev_room);

void			mod_edgeweight_path(t_graph *g, t_path *path);

/*
** visualize.c
*/

void			visualize_search(t_graph *g, t_room *room, int **matrix);
void			path_to_visualizer(t_path *p, int offset, int mod_flow);
void			print_matrix(int **matrix, int size);

/*
** ant movement functions
*/

void			move_ants(t_path **p, t_graph *g);
void			move_all_to_end(int ant_amount, char *end_room);
int				pathlen_is_optimal(t_path **p, int path_nbr, int ants_left);

#endif
