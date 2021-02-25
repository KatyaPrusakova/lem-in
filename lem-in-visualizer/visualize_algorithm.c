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
//	ft_printf("DRAW ROOM: %d line from %d -> %d |%d|%d|%d\n", room->index, room->index, room->visited_from, clr.r, clr.g, clr.b);
	SDL_RenderFillRect(renderer, &rect);
}


void draw_queue(t_room *room, char *line)
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
		room[index[1]].q = index[0];
//		draw_room(renderer, scl->room_size, &rooms[index[1]], (t_rgb){100, 0, 0, 255});
//		draw_link_bfs(renderer, scl->room_size, rooms, index);
//		draw_room(renderer, scl->room_size, &rooms[index[0]], (t_rgb){0, 0, 100, 255});
		i++;
		ft_free2d((void**)split_link);
	}
	ft_printf("Room %d queued from %d. New value: %d\n", index[1], index[0], room[index[1]].q);
	ft_free2d((void**)split_queue);
}

//void visit_room(SDL_Renderer *renderer, t_data *scl, t_room *rooms, char *line)
void		visit_room(t_room *rooms, char *line)
{
	char		**visited;
	int			index[3];

	visited = ft_strsplit(line, ' ');
	index[0] = ft_atoi(visited[0]);
	index[1] = ft_atoi(visited[1]);
	index[2] = ft_atoi(visited[2]);
	ft_printf("LINE TO VISIT ROOM: %s\n Index0: %d index1: %d index2: %d\n", line, index[0], index[1], index[2]);
	ft_printf("visit room %d\n", index[0]); //tmp
	ft_free2d((void**)visited);
	if (!index[0])
		return;
	rooms[index[0]].visited_from = index[1];
	rooms[index[0]].weight = index[2];

//	draw_room(renderer, scl->room_size, &rooms[index[0]], (t_rgb){0, 0, 100, 255});
//	draw_link_bfs(renderer, scl->room_size, rooms, index);
//	draw_room(renderer, scl->room_size, rooms, (t_rgb){200, 200, 200, 255});
//	SDL_RenderPresent(renderer);
//	SDL_Delay(500);
}


void	draw_path(t_pointers *p, t_data *scl, t_map *map, t_room *rooms, char *input)
{
	char	**split;
	int		*path;
	int		i;

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
	SDL_RenderPresent(p->renderer);
	SDL_Delay(500);
	while (--i)
	{
		ft_printf("| %d ", path[i]);
		draw_room(p->renderer, scl->room_size, rooms[path[i]], (t_rgb){0, 100, 0, 255});
		draw_link_bfs(p->renderer, scl->room_size, map, (int[2]){path[i], path[i + 1]});
		SDL_RenderPresent(p->renderer);
		SDL_Delay(500);
	}
	draw_link_bfs(p->renderer, scl->room_size, map, (int[2]){0, path[1]});
	draw_room(p->renderer, scl->room_size, rooms[0], (t_rgb){200, 200, 200, 255});
	SDL_RenderPresent(p->renderer);
	SDL_Delay(3000);
	ft_n(1);
}

void		draw_links(SDL_Renderer *renderer, int size, t_map *map)
{
	t_edge *links;

	links = map->edges;
	SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
	while (links)
	{
		draw_link_bfs(renderer, size, map, (int[2]){links->src, links->dst});
		links = links->next;
	}
}


void		draw_graph(t_pointers *p, t_data *scl, t_map *map)
{
//	t_rgb	color;473
	int		i;

	draw_links(p->renderer, scl->room_size, map);
	i = scl->room_count;
	while (i--)
	{
//		ft_printf("NAME: %s, Q: %d, VISITED: %d\n", rooms[i].name, rooms[i].q, rooms[i].visited_from);
		if (map->rooms[i].q == -1 && map->rooms[i].visited_from == -1)
			draw_room(p->renderer, scl->room_size, map->rooms[i], (t_rgb){70, 70, 70, 255});
		else if (map->rooms[i].visited_from > -1)
		{
			ft_printf("Draw visited room %d\n", i);
			draw_room(p->renderer, scl->room_size, map->rooms[i], (t_rgb){0, 0, 255, 255});
			draw_link_bfs(p->renderer, scl->room_size, map, (int[2]){i, map->rooms[i].visited_from});
		}
		else
		{
			draw_room(p->renderer, scl->room_size, map->rooms[i], (t_rgb){0, 0, 55, 255});
			draw_link_bfs(p->renderer, scl->room_size, map, (int[2]){i, map->rooms[i].q});
		}
	}
	ft_printf("PRESENT\n");
	SDL_RenderPresent(p->renderer);
	SDL_Delay(1000);
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
** Sets all visited_from and q values to -1.
*/

void	empty_rooms(t_room *rooms, int room_count)
{
	int i;

	i = 0;
	while (i < room_count)
	{
		rooms[i].visited_from = -1;
		rooms[i].q = -1;
		i++;
	}
}

/*
** Drawing the path finding algorithm before moving the ants.
*/

void	visualize_search(t_pointers *p, t_data *scl, t_map *map, char **input)
{
	int				i;

	i = move_index(input);
	draw_graph(p, scl, map);
	SDL_Delay(2000);
	while(ft_strcmp(input[i], "START_ANT_MOVEMENT"))
	{
	//	print_room_coord(map->rooms);
		if (!ft_strcmp(input[i], "BFS"))
		{
			empty_rooms(map->rooms, scl->room_count);
			i++;
		}
		if (events())
			exit(0);
		if (ft_strchr(input[i], '|'))
			draw_path(p, scl, map, map->rooms, input[i]);
		else if (!ft_strchr(input[i], '-'))
		{
			draw_queue(map->rooms, input[i + 1]);
			visit_room(map->rooms, input[i]);
		}
		draw_graph(p, scl, map);
		i++;
	}
	ft_n(1);
}

