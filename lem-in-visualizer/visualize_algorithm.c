/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:19:34 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/23 12:47:49 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

void	add_edge_weight(t_edge *links, int a, int b, int path_no)
{
	t_edge	*tmp;
	while (links)
	{
		if ((links->src == a && links->dst == b)
		|| (links->src == b && links->dst == a))
		{
			tmp = links;
			break ;
		}
		links = links->next;
	}
	if ((!tmp->weight && path_no == 1)
	|| (tmp->weight == 1 && path_no == 2))
		tmp->weight++;
	else if (path_no == 3)
	{
		tmp->weight = 3;
		tmp->rgba = RGBA_PATH;
	}
}

void	set_edge_color(t_edge *links, int a, int b, t_rgb color)
{
	while (links)
	{
		if ((links->src == a && links->dst == b)
		|| (links->src == b && links->dst == a))
		{
			links->rgba = color;
			return ;
		}
		links = links->next;
	}
}

void	draw_link_bfs(SDL_Renderer *renderer, int size, t_map *map, int i[2])
{
	t_line line;


	line.start_x = map->rooms[i[0]].x + size / 2;
	line.start_y = map->rooms[i[0]].y + size / 2;
	line.end_x = map->rooms[i[1]].x + size / 2;
	line.end_y = map->rooms[i[1]].y + size / 2;
	SDL_RenderDrawLine(renderer, line.start_x - 1, line.start_y, line.end_x - 1,\
	line.end_y);
	SDL_RenderDrawLine(renderer, line.start_x, line.start_y, line.end_x,\
	line.end_y);
	SDL_RenderDrawLine(renderer, line.start_x + 1, line.start_y, line.end_x + 1,\
	line.end_y);
	SDL_RenderDrawLine(renderer, line.start_x, line.start_y - 1, line.end_x,\
	line.end_y - 1);
	SDL_RenderDrawLine(renderer, line.start_x, line.start_y + 1, line.end_x,\
	line.end_y + 1);
}

// I give pointer to the room, not the whole array of rooms[0].

void	draw_room(SDL_Renderer *renderer, int size, t_room room, t_rgb clr)
{
	SDL_Rect	rect;

	rect.h = size;
	rect.w = size;
	rect.x = room.x;
	rect.y = room.y;
	SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
	SDL_RenderFillRect(renderer, &rect);
}


void draw_queue(t_map *map, char *line)
{
	int		i;
	int		index[2];
	char	**split_queue;
	char	**split_link;

	i = 0;
	ft_printf("%s\n", line);
	split_queue = ft_strsplit(line, ' ');
	while(split_queue[i])
	{
		split_link = ft_strsplit(split_queue[i], '-');
		index[0] = ft_atoi(split_link[0]);
		index[1] = ft_atoi(split_link[1]);
		map->rooms[index[1]].q = index[0];
		set_edge_color(map->edges, index[0], index[1], RGBA_QUEUED);
		i++;
		ft_free2d((void**)split_link);
	}
	ft_free2d((void**)split_queue);
}

void		visit_room(t_map *map, char *line)
{
	char		**visited;
	int			index[2];

	visited = ft_strsplit(line, ' ');
	index[0] = ft_atoi(visited[0]);
	index[1] = ft_atoi(visited[1]);
	ft_printf("LINE TO VISIT ROOM: %s\n Index0: %d index1: %d\n", line, index[0], index[1]);
	ft_printf("visit room %d\n", index[0]); //tmp
	ft_free2d((void**)visited);
	if (!index[0])
		return;
	map->rooms[index[0]].visited_from = index[1];
	set_edge_color(map->edges, index[0], index[1], RGBA_VISITED);
}


void	draw_path(t_pointers *p, t_data *scl, t_map *map, t_room *rooms, char *input)
{
	char	**split;
	int		*path;
	int		i;
	static int	path_no;

	path_no++;
	i = -1;
	split = ft_strsplit(input, '|');
	if (!split)
		ft_error("split fail\n");
	path = ft_memalloc(sizeof(int) * scl->room_count);
	if (!path)
		ft_error("malloc fail\n");
	while (split[++i])
		path[i] = ft_atoi(split[i]);
	draw_room(p->renderer, scl->room_size, rooms[path[--i]], (t_rgb){0, 100, 0, 255});
	draw_link_bfs(p->renderer, scl->room_size, map, (int[2]){path[i], scl->room_count - 1});
	while (i--)
	{
		ft_printf("| %d ", path[i]);
		rooms[path[i]].path = 1;
		draw_room(p->renderer, scl->room_size, rooms[path[i]], (t_rgb){0, 100, 0, 255});
		draw_link_bfs(p->renderer, scl->room_size, map, (int[2]){path[i], path[i + 1]});
		add_edge_weight(map->edges, path[i], path[i + 1], path_no);
	}
	draw_link_bfs(p->renderer, scl->room_size, map, (int[2]){0, path[1]});
	draw_room(p->renderer, scl->room_size, rooms[0], (t_rgb){200, 200, 200, 255});
	SDL_RenderPresent(p->renderer);
	SDL_Delay(1200);
	ft_n(1);
}

void		draw_links(SDL_Renderer *renderer, int size, t_map *map)
{
	t_edge *links;

	links = map->edges;
	while (links)
	{
		SDL_SetRenderDrawColor(renderer, links->rgba.r, links->rgba.g, links->rgba.b, links->rgba.a);
		draw_link_bfs(renderer, size, map, (int[2]){links->src, links->dst});
		links = links->next;
	}
}


void		edge_colors(t_edge *edges)
{
	while (edges)
	{
		if (edges->weight && !rgba_cmp(edges->rgba, RGBA_VOID))
		{
			if (edges->weight == 1)
				edges->rgba = RGBA_REVERSED;
			else if (edges->weight == 2)
				edges->rgba = RGBA_REMOVED;
			else if (edges->weight == 3)
				edges->rgba = RGBA_PATH;
		}
		edges = edges->next;
	}
}

void		draw_graph(t_pointers *p, t_data *scl, t_map *map)
{
//	t_rgb	color;473
	int		i;

	SDL_SetRenderDrawColor(p->renderer, 0, 0, 0, 255);
	SDL_RenderClear(p->renderer);
	edge_colors(map->edges);
	draw_links(p->renderer, scl->room_size, map);
	i = scl->room_count;
	while (i--)
	{
		if (!i)
			draw_room(p->renderer, scl->room_size, map->rooms[i], (t_rgb){255, 255, 255, 255});
		else if (map->rooms[i].path)
			draw_room(p->renderer, scl->room_size, map->rooms[i], RGBA_PATH);
		else if (map->rooms[i].q == -1 && map->rooms[i].visited_from == -1)
			draw_room(p->renderer, scl->room_size, map->rooms[i], RGBA_VOID);
		else if (map->rooms[i].visited_from > -1)
			draw_room(p->renderer, scl->room_size, map->rooms[i], RGBA_VISITED);
		else
			draw_room(p->renderer, scl->room_size, map->rooms[i], RGBA_QUEUED);
	}
//	ft_printf("PRESENT\n");
//	SDL_RenderPresent(p->renderer);
}


//test room coords
void	print_room_coord(t_room* room)
{
	int i;

	i = 0;
	ft_printf("ROOM COORD:\n");
	while (i < 14)
	{
		ft_printf("%d x|%d| y|%d|\n", i, room[i].x, room[i].y);
		i++;
	}
}

/*
** If the color values of a and b are the same, return 0. Else return 1.
*/

int		rgba_cmp(t_rgb a, t_rgb b)
{
	if (a.a == b.a
	&& a.r == b.r
	&& a.g == b.g
	&& a.b == b.b)
		return (0);
	else
		return (1);
}

/*
** Sets all visited_from and q values to -1.
*/

void	empty_rooms(t_edge *edges, t_room *rooms, int room_count)
{
	int i;

	i = 0;
	ft_printf("empty rooms\n");
	while (i < room_count)
	{
		rooms[i].visited_from = -1;
		rooms[i].q = -1;
		rooms[i].path = 0;
		i++;
	}
	while (edges)
	{
		if (!rgba_cmp(edges->rgba, RGBA_QUEUED)
		|| !rgba_cmp(edges->rgba, RGBA_VISITED))
		{
			edges->rgba = RGBA_VOID;
			ft_printf("Set color to void %d %d\n", edges->dst, edges->src);
		}
		edges = edges->next;
	}
}

/*
** Drawing the path finding algorithm before moving the ants.
*/

void	visualize_search(t_pointers *p, t_data *scl, t_map *map, char **input)
{
	int				i;
	int				pause;

	i = move_index(input, "");
	draw_graph(p, scl, map);
	SDL_RenderPresent(p->renderer);
	SDL_Delay(1000);
	while(ft_strcmp(input[i], "START_ANT_MOVEMENT"))
	{
		pause = events();
		if (pause % 2 == 0)
		{
			if (!ft_strcmp(input[i], "BFS"))
			{
				ft_printf("BFS\n");
				empty_rooms(map->edges, map->rooms, scl->room_count);
				draw_graph(p, scl, map);
				i++;
			}
			draw_graph(p, scl, map);
			if (ft_strchr(input[i], '|'))
			{
				ft_printf("Draw path\n");
				draw_path(p, scl, map, map->rooms, input[i]);
			}
			else if (!ft_strchr(input[i], '-'))
			{
				ft_printf("Add queue\n");
				draw_queue(map, input[i + 1]);
				visit_room(map, input[i]);
			}
			i++;
			SDL_RenderPresent(p->renderer);
			SDL_Delay(200);
		}
	}
	ft_n(1);
}

