/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/14 23:00:33 by eprusako         ###   ########.fr       */
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
	
	//ft_dprintf(fd, "i is %d\nant is %d\n", i, ant);
	return (i);
}

int		valid_ants(int flag, char **line)
{
	int		i;
	int		ant;

	i = 0;
	i = is_comment(line, i);
	ant = ft_atoi(line[i]);
	if (!line[i] || !(ft_strisdigit(line[i])) || ant <= 0 || ant >= 2147483647)
		print_error(3);
	i = is_comment(line, i + 1);
	return(flag == 1 ? i : ant);
}