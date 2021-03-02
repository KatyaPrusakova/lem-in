/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:17:33 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/02 11:10:58 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin_visual.h"

void	ft_error(const char *str_err)
{
	ft_printf("%s\n", str_err);
	exit(0);
}

char	**ft_realloc(char **input, int len)
{
	char **tmp;

	tmp = ft_memalloc(sizeof(char*) * (len * 2 + 1));
	tmp = ft_memcpy(tmp, input, sizeof(char*) * len);
	free(input);
	return(tmp);
}

char	**parse_input(void)
{
	char	**input;
	char	*line;
	int		i;
	int		buf;

	i = 0;
	buf = 10000;
	input = ft_memalloc(sizeof(char*) * buf + 1);
	while (get_next_line(0, &line) == 1)
	{
		if (i == buf)
		{
			input = ft_realloc(input, buf);
			buf += buf;
		}
		input[i++] = line;
	}
	ft_printf("amount of lines = %d\n", i); //test
	return (input);
}

/*
** Locates the first row of lem-in output and returns it as int index.
*/

int		move_index(char **input, char *find)
{
	static int i;

	while (ft_strcmp(input[i], find))
		i++;
	ft_printf("Row %d is empty\n", i);
	i++;
	return (i);
}

int			events(void)
{
	SDL_Event		event;
	static int		pause;

	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		if (event.key.keysym.sym == SDLK_SPACE
		&& event.key.type == SDL_KEYUP)
		{
			ft_printf("SPACE\n");
			pause++;
		}
	}
	return (pause);
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



void		visualize_ants(t_pointers *sdl, t_data *scale, t_map *map, char **input)
{
	t_ant	*list;
	int		i;
	int		wave;
	int		pause;

	list = NULL;
	i = move_index(input, "START_ANT_MOVEMENT");
	ft_printf("Index i = %d\n", i);
	wave = 0;
	while (input[i])
	{
		pause = events();
		if (pause % 2)
		{
			if (!ft_strcmp("0 0", input[i]))
			{
				ft_printf("stop\n");
				break;
			}
			list = ant_destinations(input[i], list, map->rooms, wave);
			SDL_Delay(300);
			while (move_ants(sdl, list, scale, map))
				SDL_Delay(2);
			i++;
			wave++;
		}
	}
	if (list)
		list = free_ants(list);
	SDL_Delay(3000);
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
	ft_printf("saved rooms\n");
	sdl = initialize(&scale, sdl, map.rooms);
	visualize_search(sdl, &scale, &map, input);
	visualize_ants(sdl, &scale, &map, input);
	kill_all(sdl, map, input);
	return (0);
}
