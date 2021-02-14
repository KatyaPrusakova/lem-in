/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/14 12:44:08 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// should it take comment on line[0] before ant number?
void			parse_ants(char *line, t_graph* data)
{
	int		ant;

	ant = ft_atoi(line);
	ft_dprintf(fd, "%d\n", ant);
	if (!line || !(ft_strisdigit(line)) || ant <= 0 || ant >= 2147483647) //limit?
		print_error(3);
	data->ants = ant;
}
