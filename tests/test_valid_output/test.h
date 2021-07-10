/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 20:02:29 by ksuomala          #+#    #+#             */
/*   Updated: 2021/04/27 21:26:12 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "libft.h"
# define ROOM_FULL "L%d cannot move to %s. Room already has an ant.\n"
# define NO_LINK "Tried to move L%d from %s-%s. Rooms are not connected\n"

typedef struct s_room
{
	char	*name;
	int		ant;
}				t_room;

int			g_total_rooms;
int			g_total_ants;

void		create_rooms(char **input, t_room **room_array);
int			**create_matrix(char **input, t_room *room_array);
void		check_moves(char **input, t_room *rooms, int **ad_matrix);
void		error_exit(char *str);
int			name_to_index(t_room *array, char *name);

#endif