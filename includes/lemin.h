/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:32:15 by eprusako          #+#    #+#             */
/*   Updated: 2021/04/20 14:04:56 by ksuomala         ###   ########.fr       */
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

typedef	struct		s_search
{
	struct s_queue	*q;
	struct s_room	*tmp;
	struct s_room	*room;
	struct s_path	*path;
	struct s_path	**set;
	int				*visited;
	int				path_no;
	int				continue_alternative_edges;
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
	int				ants_end;
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
	int				queue; //added
	int				ant;
	char			*name;
	t_room			*room;
	struct s_path	*end; //paths are null terminated. Why do you need end pointer?
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

int					check_weight(int link_weight, int set_weight);


/*
** MALLOC_FREE.C
*/

t_graph*			create_graph(int rooms);
t_path*				free_path(t_path *path);
t_path**			free_path_set(t_path ***set);



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
char				*ft_firstword(char **line, int i);

//draft

t_path				*bfs(t_graph *g, int edge_w, int start, int end);
t_search			init_search(t_graph *g, int mod_edge, int start, int end);
t_path				**bfs_set(t_graph *graph, int edge_w, int start, int end);
int					bfs_set_modify(t_graph *graph, int edge_w, int start, int end);

int					end_is_neighbour(t_room *head, int end);
t_path 				**unlimited_flow(void);
t_path				**edmonds(t_graph *g);



//DFS

t_path				*dfs_find_path(t_graph *g, t_room *current, t_search s);
t_path				**dfs_mod_edges(t_graph *g, t_room *current, t_search s, int *visited);
t_path				**dfs_mod_all(t_graph *g, t_room *current, t_search *s, int *visited);
t_path				**bfs_set_weightend(t_graph *graph, int edge_w, int start, int end);
t_path **set_search_to_modifyPaths(t_graph *g);







t_path				*mod_path(int *visited, int link_index, /*int **matrix, */int end_room);


//queue functions

t_queue				*enqueue(int index, t_queue *q, t_room **adlist, int prev);
t_queue				*dequeue(t_queue *q);

/*
** path finding
*/

t_path				**find_paths(t_graph *graph);
t_path				**find_sets(t_graph *graph);
void				print_paths(t_path **path);

/*
** path_calculations.c
*/

int					count_max_paths(t_graph *graph);
int					set_rooms_total(t_path **set, int last_room);
int					paths_in_array(t_path **set);
int					path_cmp(t_path *p1, t_path *p2);


/*
** sort_adlist.c
*/

t_room		*adlist_mergesort(t_room *head, int start, int **weight_matrix);

/*
** save_path.c
*/

int			check_path(t_graph *graph, t_search s, int link_index, int *path_no);
t_path		*save_path(int *visited, int find_path, t_graph *g, t_search s);


int			**mod_edgeweight_path(int **matrix, t_path *path);
int			**mod_edgeweight_set(int **matrix, t_path **set);




/*
** visualize.c
*/

void	visualize_search(t_room *room, t_queue *q, int **matrix);


//void				queue_to_visualizer(t_room **adlist, t_queue *q, int visualize); //testing
//void				visited_to_visualizer(int current_index, int visited_from, int visualize);

/*
** ANTS_FLOW.C
*/

int					*allocate_ants_to_rooms(t_path **path, t_graph *graph);

//test

void	print_matrix(int **matrix, int size);

/*
** ant movement functions
*/

void		move_ants(t_path **p, t_graph *g);
int			pathlen_is_optimal(t_path **p, int path_nbr, int ants_left);





#endif
