/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:17:33 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/24 16:26:01 by ksuomala         ###   ########.fr       */
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



void		visualize_ants(t_pointers *sdl, t_data *scale, t_room *rooms, char **input)
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
		if (!ft_strcmp("0 0", input[i]))
		{
			ft_printf("stop\n");
			break;
		}
		list = ant_destinations(input[i], list, rooms, wave);
		SDL_Delay(300);
		while (move_ants(sdl, list, scale))
		 	SDL_Delay(2);
		i++;
		wave++;
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
	visualize_ants(sdl, &scale, map.rooms, input);
	kill_all(sdl, map, input);
}
