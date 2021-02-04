/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:08:16 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/04 22:08:57 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_graph*		create_graph(int rooms) 
{
	t_graph		*new;

	new = ft_memalloc(sizeof(t_graph));
	new->adlist = ft_memalloc(sizeof(t_room*) * (rooms+1));
	new->room_total = rooms;
	return (new);
}