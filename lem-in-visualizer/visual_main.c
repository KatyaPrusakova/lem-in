/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:17:33 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/15 17:20:35 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "lemin_visual.h"

void	ft_error(const char *str_err)
{
	ft_printf("%s\n", str_err);
	exit(0);
}

char	**parse_input(void)
{
	char	**input;
	char	*line;
	int		i;
	int		buf;

	i = -1;
	buf = 10000;
	input = ft_memalloc(sizeof(char*) * buf + 1);
	while ((x = get_next_line(0, &line)) > 0)
	{
		input[i] = line;
		if (i == 9999)
		{
			ft_printf("9999999999999999999999999999999999\n");
			exit(0);
		}
	}
	ft_printf("amount of lines = %d\n", i); //test
	return (input);
}

/*
** Locates the first row of lem-in output and returns it as int index.
*/

int		move_index(char **input)
{
	static int i;

	while (ft_strcmp(input[i], ""))
		i++;
	return (i + 1);
}

int			events(void)
{
	SDL_Event		event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		return (1);
	return (0);
}

/*
// test function
*/

void 	print_rooms(t_room *room, int room_count)
{
	int i;

	i = 0;

	while (i < room_count)
	{
		ft_printf("room %s x = %d y = %d\n", room[i].name, room[i].x, room[i].y);
		i++;
	}
}


void		play(t_pointers *sdl, t_data *scale, t_room *rooms, char **input)
{
	t_ant	*list;
	int		i;
	int		wave;

	list = NULL;
	i = move_index(input);
	wave = 0;
	SDL_SetRenderTarget(sdl->renderer, NULL);
	while (!events() && input[i])
	{
		list = ant_destinations(input[i], list, rooms, wave);
		SDL_Delay(300);
		while (move_ants(sdl, list, scale))
		 	SDL_Delay(2);
		i++;
		wave++;
	}
	SDL_Delay(3000);
	exit(0);
}

void		kill_all(t_pointers *sdl, t_map map, char **input)
{
	int		i;
	t_ant	*ant;
	t_edge	*edge;

	ft_free2d((void**)input);
	SDL_DestroyTexture(sdl->backround);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	free(sdl);
	i = 0;
	while (map.rooms[i].name)
	{
		ft_strdel(&map.rooms[i].name);
		ft_printf("del room name\n"); //test
		i++;
	}
	free(map.rooms);
	ant = map.ants;
	while(ant)
	{
		ant = map.ants->next;
		ft_memdel((void*)&map.ants);
		map.ants = ant;
	}
	edge = map.edges;
	while(edge)
	{
		edge = map.edges->next;
		ft_strdel(&map.edges->dst);
		ft_strdel(&map.edges->src);
		ft_memdel((void*)&map.edges);
		map.edges = edge;
	}
	SDL_Quit();
	exit(0);
}

int			main(void)
{
	t_pointers	*sdl;
	t_data		scale;
	t_map		map;
	char		**input;

	sdl = ft_memalloc(sizeof(t_pointers));
	if (!sdl)
		ft_error("malloc fail");
	input = parse_input();
	scale = scale_map(input);

	map = save_rooms(input, scale.room_count);


	sdl = initialize(&map, &scale, sdl);
	SDL_Delay(3000);

	ft_printf("MAP ROOM SIZE = %d\n", scale.room_size); //test
	draw_algorithm(sdl, &scale, map.rooms, input);
//	play(sdl, &scale, map.rooms, input);
//	kill_all(sdl, map, input);
}
