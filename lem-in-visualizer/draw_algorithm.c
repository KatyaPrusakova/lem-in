/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:19:34 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/23 11:50:25 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

void	draw_room(SDL_Renderer *renderer, int size, t_room *room, t_rgb clr)
{
	SDL_Rect	rect;

	rect.h = size;
	rect.w = size;
	rect.x = room->x;
	rect.y = room->y;
	SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
	SDL_RenderFillRect(renderer, &rect);
}

void	draw_link_bfs(SDL_Renderer *renderer, int size, t_room *rooms, int i[2])
{
	t_line line;

	ft_printf("line from room %d - %d\n", i[0], i[1]);
	line.start_x = rooms[i[0]].x + size / 2;
	line.start_y = rooms[i[0]].y + size / 2;
	line.end_x = rooms[i[1]].x + size / 2;
	line.end_y = rooms[i[1]].y + size / 2;

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

void draw_queue(SDL_Renderer *renderer, t_data *scl, t_room *rooms, char *line)
{
	int		i;
	int		index[2];
	char	**split_queue;
	char	**split_link;

	i = 0;
	split_queue = ft_strsplit(line, ' ');
	while(split_queue[i])
	{
		split_link = ft_strsplit(split_queue[i], '-');
		index[0] = ft_atoi(split_link[0]);
		index[1] = ft_atoi(split_link[1]);
		draw_room(renderer, scl->room_size, &rooms[index[1]], (t_rgb){100, 0, 0, 255});
		draw_link_bfs(renderer, scl->room_size, rooms, index);
		draw_room(renderer, scl->room_size, &rooms[index[0]], (t_rgb){0, 0, 100, 255});
		i++;
	}
}

void visit_room(SDL_Renderer *renderer, t_data *scl, t_room *rooms, char *line)
{
	char		**visited;
	int			index[2];

	visited = ft_strsplit(line, ' ');
	index[0] = ft_atoi(visited[0]);
	index[1] = ft_atoi(visited[1]);
	ft_printf("visit room %d\n", index[0]); //tmp
	if (!index[0])
		return;
	draw_room(renderer, scl->room_size, &rooms[index[0]], (t_rgb){0, 0, 100, 255});
	draw_link_bfs(renderer, scl->room_size, rooms, index);
	draw_room(renderer, scl->room_size, rooms, (t_rgb){200, 200, 200, 255});
	SDL_RenderPresent(renderer);
	SDL_Delay(500);
}


void	draw_path(t_pointers *p, t_data *scl, t_room *rooms, char *input)
{
	char	**split;
	int		*path;
	int		i;

	i = 0;
	ft_printf("input %s\n", input);
	split = ft_strsplit(input, '|');
	if (!split)
		ft_error("split fail\n");
	path = ft_memalloc(sizeof(int) * scl->room_count);
	if (!path)
		ft_error("malloc fail\n");
	ft_printf("Draw path:\n");
	while (split[i])
	{
		ft_printf("split %d = %d\n", i, ft_atoi(split[i]));
		path[i] = ft_atoi(split[i]);
		ft_printf("i = %d path[%d] = %d\n", i, i, path[i]);
		i++;
	}
	draw_room(p->renderer, scl->room_size, &rooms[path[--i]], (t_rgb){0, 100, 0, 255});
	draw_link_bfs(p->renderer, scl->room_size, rooms, (int[2]){path[i], scl->room_count - 1});
	SDL_RenderPresent(p->renderer);
	SDL_Delay(500);
	while (--i)
	{
		ft_printf("draw room %d\n", path[i]);
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

/*
** Drawing the path finding algorithm before moving the ants.
*/

void	draw_algorithm(t_pointers *p, t_data *scl, t_room *rooms, char **input)
{
	int				i;

	SDL_SetRenderTarget(p->renderer, NULL);
	SDL_RenderCopy(p->renderer, p->backround, NULL, NULL);
	SDL_RenderPresent(p->renderer);
	SDL_Delay(2000);
	i = move_index(input);
	while(ft_strcmp(input[i], "START_ANT_MOVEMENT"))
	{
		if (!events())
			break;
		if (ft_strchr(input[i], '|'))
			draw_path(p, scl, rooms, input[i]);
		else if (!ft_strchr(input[i], '-'))
		{
			draw_queue(p->renderer, scl, rooms, input[i + 1]);
			visit_room(p->renderer, scl, rooms, input[i]);
		}
		i++;
	}
	ft_n(1);
	SDL_Delay(3000);
}

