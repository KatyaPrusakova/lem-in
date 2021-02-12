/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:19:34 by ksuomala          #+#    #+#             */
/*   Updated: 2021/02/12 14:17:32 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"
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

void visit_room(SDL_Renderer *renderer, t_data *scl, t_room *rooms, char *line)
{
	SDL_Rect	room;
	char		**visited;
	int			index[2];

	visited = ft_strsplit(line, ' ');
	index[0] = ft_atoi(visited[0]);
	index[1] = ft_atoi(visited[1]);
	ft_printf("visit room %d\n", visited[0]); //tmp
	room.h = scl->room_size;
	room.w = room.h;
	room.x = rooms[index[0]].x;
	room.y = rooms[index[0]].y;
	SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
	SDL_RenderFillRect(renderer, &room);
	draw_link_bfs(renderer, scl->room_size, rooms, index);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
}

/*
** Drawing the path finding algorithm before moving the ants.
*/

void	draw_algorithm(t_pointers *p, t_data *scl, t_room *rooms, char **input)
{
	int				i;
//	t_room			*visited;
//	t_edge			*edges;
//	t_room			*q;

	SDL_SetRenderTarget(p->renderer, NULL);
	SDL_RenderCopy(p->renderer, p->backround, NULL, NULL);
	SDL_RenderPresent(p->renderer);
	SDL_Delay(2000);
	i = move_index(input);
	while(ft_strcmp(input[i], "START_ANT_MOVEMENT"))
	{
		if (!ft_strchr(input[i], '-'))
		{
			ft_printf("%s\n", input[i]);
			visit_room(p->renderer, scl, rooms, input[i]);
		//	ft_printf("visited %s\n", input[i]);
		}
		else
		{
			ft_printf(" %s", input[i]);
		}
		i++;
	}
	ft_n(1);
	if (!ft_strcmp(input[i], "START_ANT_MOVEMENT"))
		ft_printf("path found\n");
}

