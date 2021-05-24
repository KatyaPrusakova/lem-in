#include "lemin_visual.h"

t_ant		*ant_movement(char *line, t_ant *list, t_map *map, int *wave)
{
	if (!ft_strchr(line, 'L') && !ft_strchr(line, '-'))
		return (list);
	list = ant_destinations(line, list, map->rooms, *wave);
	*wave += 1;
	return (list);
}

void		visualize_ants(t_pointers *sdl, t_data *scale, t_map *map, char **input)
{
	t_ant	*list;
	int		i;
	int		wave;
	int		pause;

	list = NULL;
	i = move_index(input, "");
	wave = 0;
	while (input[i])
	{
		pause = events();
		if (pause % 2)
		{
			ft_printf("loop\n");
			if (!ft_strcmp("0 0", input[i]))
				break;
			//list = ant_destinations(input[i], list, map->rooms, wave);
			list = ant_movement(input[i], list, map, &wave);
			SDL_Delay(ANT_DELAY);
			while (move_ants(sdl, list, scale, map))
				SDL_Delay(1);
			i++;
			//wave++;
		}
	}
	if (list)
		list = free_ants(list);
	SDL_Delay(3000);
}
