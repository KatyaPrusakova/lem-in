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

void	draw_link_bfs(SDL_Renderer *renderer, int size, t_room *rooms, int i[2])
{
	t_line line;


//coordinates here get changed on the way ant that breaks the line drawing.
	ft_printf("line from room %d - %d\n", i[0], i[1]);
	line.start_x = rooms[i[0]].x + size / 2;
	line.start_y = rooms[i[0]].y + size / 2;
	line.end_x = rooms[i[1]].x + size / 2;
	line.end_y = rooms[i[1]].y + size / 2;


	ft_printf("line from %d|%d -> %d|%d\n\n", line.start_x, line.start_y, line.end_x, line.end_y);
	if (i[0] < 0 || i[1] < 0)
		ft_printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  \n");
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

void	draw_room(SDL_Renderer *renderer, int size, t_room *room, t_rgb clr)
{
	SDL_Rect	rect;

	rect.h = size;
	rect.w = size;
	rect.x = room->x;
	rect.y = room->y;
	ft_printf("Draw room %d\n", room->index);
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


void	draw_path(t_pointers *p, t_data *scl, t_room *rooms, char *input)
{
	char	**split;
	int		*path;
	int		i;

	i = 0;
//	ft_printf("input %s\n", input);
	split = ft_strsplit(input, '|');
//	if (!split)
//		ft_error("split fail\n");
	path = ft_memalloc(sizeof(int) * scl->room_count);
	if (!path)
		ft_error("malloc fail\n");
//	ft_printf("Draw path:\n");
	while (split[i])
	{
//		ft_printf("split %d = %d\n", i, ft_atoi(split[i]));
		path[i] = ft_atoi(split[i]);
//		ft_printf("i = %d path[%d] = %d\n", i, i, path[i]);
		i++;
	}
	draw_room(p->renderer, scl->room_size, &rooms[path[--i]], (t_rgb){0, 100, 0, 255});
	draw_link_bfs(p->renderer, scl->room_size, rooms, (int[2]){path[i], scl->room_count - 1});
	SDL_RenderPresent(p->renderer);
	SDL_Delay(500);
	while (--i)
	{
	//	ft_printf("draw room %d\n", path[i]);
		draw_room(p->renderer, scl->room_size, &rooms[path[i]], (t_rgb){0, 100, 0, 255});
		draw_link_bfs(p->renderer, scl->room_size, rooms, (int[2]){path[i], path[i + 1]});
		SDL_RenderPresent(p->renderer);
		SDL_Delay(500);
	}
	draw_link_bfs(p->renderer, scl->room_size, rooms, (int[2]){0, path[1]});
	draw_room(p->renderer, scl->room_size, rooms, (t_rgb){200, 200, 200, 255});
	SDL_RenderPresent(p->renderer);
	SDL_Delay(500);
}

void		draw_links(SDL_Renderer *renderer, int size, t_room *room, t_edge *links)
{
	SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
	while (links)
	{
		draw_link_bfs(renderer, size, room, (int[2]){links->src, links->dst});
		links = links->next;
	}
}


void		draw_graph(t_pointers *p, t_data *scl, t_room *rooms, t_edge *links)
{
//	t_rgb	color;473
	int		i;

	draw_links(p->renderer, scl->room_size, rooms, links);
	i = scl->room_count;
	while (i--)
	{
//		ft_printf("NAME: %s, Q: %d, VISITED: %d\n", rooms[i].name, rooms[i].q, rooms[i].visited_from);
		if (rooms[i].q == -1 && rooms[i].visited_from == -1)
		{
			draw_room(p->renderer, scl->room_size, &rooms[i], (t_rgb){70, 70, 70, 255});
		}
		else if (rooms[i].visited_from > -1)
		{
			if (rooms[i].weight == 1)
				SDL_SetRenderDrawColor(p->renderer, 50, 50, 0, 255);
			else if (rooms[i].weight == -1)
				SDL_SetRenderDrawColor(p->renderer, 0, 50, 50, 255);
			else
				SDL_SetRenderDrawColor(p->renderer, 0, 0, 255, 255);
			draw_link_bfs(p->renderer, scl->room_size, rooms, (int[2]){i, rooms[i].visited_from});
			draw_room(p->renderer, scl->room_size, &rooms[i], (t_rgb){0, 0, 255, 255});
			ft_printf("Visited node %d\n", i);
		}
		else
		{
			draw_room(p->renderer, scl->room_size, &rooms[i], (t_rgb){0, 0, 55, 255});
			draw_link_bfs(p->renderer, scl->room_size, rooms, (int[2]){i, rooms[i].q});
			ft_printf("Queued room %d\n", i);
		}
	}
	ft_printf("PRESENT\n");
	SDL_RenderPresent(p->renderer);
	SDL_Delay(500);
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
** Drawing the path finding algorithm before moving the ants.
*/

void	visualize_search(t_pointers *p, t_data *scl, t_map *map, char **input)
{
	int				i;

	i = move_index(input);
	draw_graph(p, scl, map->rooms, map->edges);
	SDL_Delay(2000);
	while(ft_strcmp(input[i], "START_ANT_MOVEMENT"))
	{
	//	print_room_coord(map->rooms);
		if (events())
			break;
		if (ft_strchr(input[i], '|'))
			draw_path(p, scl, map->rooms, input[i]);
		else if (!ft_strchr(input[i], '-'))
		{
			draw_queue(map->rooms, input[i + 1]);
			//visit_room should only save the room it was visited from, and the edge value. Add one more number to the input as the edge value.
			visit_room(map->rooms, input[i]);
			SDL_Delay(1000);
		}
		draw_graph(p, scl, map->rooms, map->edges);
		//draw visited rooms, unvisited rooms and links, start and end rooms.
		i++;
	}
	ft_n(1);
}

