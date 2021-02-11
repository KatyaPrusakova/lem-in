/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/11 12:40:19 by eprusako         ###   ########.fr       */
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
<<<<<<< HEAD
		if (i == len)
		{
			input = ft_realloc(input, len);
			len += len;
		}
		input[i] = line;
		i++;
	}
	print_2dstr(input);
	return (input);
=======
		if (!line[i][0])
			print_error(7);
		ft_printf("%s\n", line[i]);
		i++;
	}
	ft_n(1);
	if (!i)
		print_error(8);
	return (line);
>>>>>>> 214cee6fa440ef209da04e948a385c2eb2d508ff
}

