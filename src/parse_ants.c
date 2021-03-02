/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/03/02 16:36:36 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			is_comment(char **str, int i)
{
	if (str[i][0] == '#')
		i++;
	return (i);
}

int			parse_ants(char **line, t_graph *data)
{
	int		i;
	int		ant;

	ant = valid_ants(0, line);
	data->ants = ant;
	i = valid_ants(1, line);
	return (i);
}

/*
** int flag created so that function returns two things
** flag = 0 case: index i from input
** flag = 1 case: number of ants
** then number of ants is checked if it is valid, before return
*/

int			valid_ants(int flag, char **input)
{
	int		i;
	int		ant;

	i = 0;
	while (input[i][0] == '#')
		i++;
	ant = ft_atoi(input[i]);
	if (!input[i] || !(ft_strisdigit(input[i])) || ant <= 0 || ant > 2147483647)
		print_error(3, input);
	i = is_comment(input, i + 1);
	return (flag == 1 ? i : ant);
}
