/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_exists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:08:16 by eprusako          #+#    #+#             */
/*   Updated: 2021/06/21 19:24:13 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	link_exists(t_graph *g, int a, int b)
{
	t_room	*tmp;

	tmp = g->adlist[a]->next;
	while (tmp)
	{
		if (tmp->index == b)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
