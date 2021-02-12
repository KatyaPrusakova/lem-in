#ifndef _LEM_IN_VISUAL_
# define _LEM_IN_VISUAL_

# define WIN_W 950
# define WIN_H 950
# define PI  3.14159

# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL_ttf.h>
#include <math.h>


typedef struct	s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}				t_rgb;

typedef	struct s_line
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;
}				t_line;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
}				t_room;

typedef struct	s_ant
{
	int				i;
	float			x;
	float			y;
	float			dest_x;
	float			dest_y;
	int				wave;
	struct s_ant	*next;
}				t_ant;


typedef struct	s_edge
{
	char			*src;
	char 			*dst;
	struct s_edge	*next;
}				t_edge;

/*
** This is where most of our data is stored. *ants represents the head node
** of a linked list containing information of ants and their movements.
**
** *rooms is an array of t_room elements.
** *edges is the head element of a linked list containing all the edges between
** vertices in the maze.
*/

typedef struct s_map
{
	int		count;
	t_ant	*ants;
	t_room	*rooms;
	t_edge	*edges;
}				t_map;

typedef struct s_data
{
	int	room_count;
	int	room_size;
	int	win_w;
	int	max_y;
	int	max_x;
	int	ants;
} t_data;

typedef struct		s_bfs
{
	char	**queue;
	int		*visited;
}					t_bfs;


typedef struct		s_pointers
{
	SDL_Texture		*backround;
	SDL_Renderer	*renderer;
	SDL_Window		*window;

}					t_pointers;


/*
** Functions in save_graph.c. These are used to read data from the stdin
** and save it to t_data and t_map data types.
*/

t_data		scale_map(char **input);
t_room		add_room(char *line);
t_edge		*new_edge(t_edge *head, char *src, char *dst);
t_edge		*add_edges(char **input, int room_count);
t_map		save_rooms(char **input, int room_count);
int			move_index(char **input);

/*
**
*/

void	ft_error(const char *str_err);

/*
**
*/

t_pointers	*initialize(t_map *map, t_data *scale, t_pointers *sdl);

t_room	*find_room(char *name, t_room *list);
t_ant	*ant_destinations(char *line, t_ant *head, t_room *room, int wave);

/*
** Drawing the path finding algorithms.
*/

void	draw_algorithm(t_pointers *p, t_data *scl, t_room *rooms, char **input);


/*
** These functions are used to draw ant movement on the screen
*/

int move_ants(t_pointers *sdl, t_ant *head, t_data *scale);

SDL_Renderer	*links(SDL_Renderer *renderer, int size, t_map *map);


#endif
