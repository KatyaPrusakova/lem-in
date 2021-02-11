/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/11 12:48:02 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	**ft_realloc(char **input, int fd)
{
	char **tmp;

	tmp = ft_memalloc(sizeof(char*) * (fd * 2));
	tmp = ft_memcpy(tmp, input, sizeof(char*) * fd);
	free(input);
	return(tmp);
}

char **parse_input(char **av)
{
	int i;
	int len;
	int fd_test = 0;
	char *line;
	char **input;

	i = 0;
	len = 5;
	fd_test = open(av[1], O_RDWR);
	input = ft_memalloc(sizeof(char*) * len);
	while (get_next_line(fd_test, &line))
	{
		if (i == len)
		{
			input = ft_realloc(input, len);
			len += len;
		}
		input[i] = line;
		i++;
	}
//	print_2dstr(input);
	return (input);
}

