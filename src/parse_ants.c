/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/24 10:27:31 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_comment(char **str, int i)
{
	while (str[i][0] == '#' && ft_strcmp(str[i], "##start") && ft_strcmp(str[i], "##end"))
		i++;
	return (i);
}

int			parse_ants(char **line, t_graph* data)
{
	int		i;
	int		ant;

	ant = valid_ants(0, line);
	data->ants = ant;
	i = valid_ants(1, line);
	return (i);
}

int		valid_ants(int flag, char **input)
{
	int		i;
	int		ant;

	i = 0;
	i = is_comment(input, i);
	ant = ft_atoi(input[i]);
	if (!input[i] || !(ft_strisdigit(input[i])) || ant <= 0 || ant > 2147483647)
		print_error(3, input);
	i = is_comment(input, i + 1);
	return(flag == 1 ? i : ant);
}