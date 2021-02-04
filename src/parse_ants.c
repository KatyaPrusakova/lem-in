/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/05 00:30:50 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// should it take comment on line[0] before ant number?
void			parse_ants(char *line, t_graph* data)
{
	int		ant;

	ant = ft_atoi(line);
	if (!line || !(ft_strisdigit(line)) || ant <= 0 || ant > 2147483647) //limit?
		print_error(2);
	data->ants = ant;
}