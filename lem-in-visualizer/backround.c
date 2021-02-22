/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backround.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:59:26 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/22 22:39:47 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"

/*
** Getting the coordinates. src is used to locate the right t_room structure
** that contains that rooms x and y coordinates.
*/

t_line			path_coordinates(char *src, char *dst, t_room *rooms, int size)
{
	t_line	line;
	int		i;

	ft_printf("src %s dst %s\n", src, dst);
	i = 0;
	while (ft_strcmp(rooms[i].name, src))
		i++;
	line.start_x = rooms[i].x + size / 2;
	line.start_y = rooms[i].y + size / 2;
	i = 0;
	while (ft_strcmp(rooms[i].name, dst))
		i++;
	line.end_x = rooms[i].x + size / 2;
	line.end_y = rooms[i].y + size / 2;
	return (line);
}

/*
** Drawing lines between the linked rooms.
*/

SDL_Renderer	*links(SDL_Renderer *renderer, int size, t_map *map)
{
	t_edge	*tmp;
	t_line	line;

	//issue here. src and dst null.
	tmp = map->edges;
	while (tmp)
	{
		line = path_coordinates(tmp->src, tmp->dst, map->rooms, size);
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
		tmp = tmp->next;
	}
	return (renderer);
}

/*
** Creating the backround. The rooms and the paths between them for the ants
** to move in. This will be taken from the screen and converted into a
** backround SDL_Texture * format later.
*/

int			background(t_data *scale, t_map *map, t_pointers *sdl)
{
	int size;
	int i;

	SDL_SetRenderTarget(sdl->renderer, sdl->backround); //Setting the renderer target to backround texture.
	i = 0;
	size = (scale->max_y > scale->max_x) ? scale->max_y : scale->max_x;
	if (size < 2)
		size++;
	size = WIN_W / size * 0.7;
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl->renderer);
	while (i < map->count)
	{
//		ft_printf("bg room count %d\n", map->count); //test
		map->rooms[i].x = map->rooms[i].x * size + 50;
		map->rooms[i].y = map->rooms[i].y * size + 50;
		draw_room(sdl->renderer, size, &map->rooms[i], (t_rgb){79, 79, 79, 255});
		i++;
	}
	sdl->renderer = links(sdl->renderer, size, map);
	draw_room(sdl->renderer, size, &map->rooms[0], (t_rgb){200, 200, 200, 255});
	draw_room(sdl->renderer, size, &map->rooms[map->count - 1], (t_rgb){35, 35, 35, 255});
	SDL_RenderPresent(sdl->renderer);
	return (size);
}

/*
** Initializing SDL2. Creating the window and renderer.
*/

t_pointers	*initialize(t_map *map, t_data *scale, t_pointers *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_error(SDL_GetError());
//	if (TTF_Init() == -1)
//		ft_error(SDL_GetError());
	if (!(sdl->window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_UNDEFINED, WIN_W + 50, WIN_H + 50, 0)))
		ft_error(SDL_GetError());
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0)))
		ft_error(SDL_GetError());
	sdl->backround = SDL_CreateTexture(sdl->renderer,\
	SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIN_H + 50, WIN_W + 50);
	if (!sdl->backround)
		ft_error(SDL_GetError());
	scale->room_size = background(scale, map, sdl);
	return (sdl);
}
