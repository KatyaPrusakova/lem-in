/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:13:14 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/19 21:08:41 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visual.h"



int			room_size(t_data *scale)
{
	int size;

	size = (WIN_H / scale->max_y > WIN_W / scale->max_x) ? scale->max_y : scale->max_x;
	//ft_printf("size = %d\n", size);
	if (size < 2)
		size++;
	if (size > WIN_H && !scale->pos)
		ft_error("The map is too big\n");
	size = (WIN_H - 50) / size * 0.75;
	if (!size)
		size = 2;
	ft_printf("room size %d\n", size);
	return (size);
}


t_data	scale_map(char **input)
{
	t_data	new;
	char	**split;
	int		i;
	int		nb;

	ft_bzero(&new, sizeof(t_data));
	i = 0;
	new.ants = ft_atoi(input[0]);
	while (ft_strchr(input[++i], ' ') || input[i][0] == '#')
	{
		if (input[i][0] != '#')
		{
			new.room_count += 1;
//			//ft_printf("input line %s\n", input[i]); //test
			split = ft_strsplit(input[i], ' ');
			if (!split)
				ft_error("ft_strsplit fail");
			if ((nb = ft_atoi(split[1])) > new.max_x)
				new.max_x = nb;
			if ((nb = ft_atoi(split[2])) > new.max_y)
				new.max_y = nb;
			ft_free2d((void**)split);
		}
	}
//	//ft_printf("i = %d\n", i);
	return (new);
}
