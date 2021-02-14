/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/14 21:36:09 by eprusako         ###   ########.fr       */
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

char		**parse_input(void)
{
	int i;
	int len;
//	int fd;// delete
	char *line;
	char **input;

	i = 0;
	len = 5;
//	fd = open(av[1], O_RDWR);//delete
	input = ft_memalloc(sizeof(char*) * len);
	while (get_next_line(0, &line))
	{
		//ft_dprintf(fd, "%s\n", line); 
		if (i == len)
		{
			input = ft_realloc(input, len);
			len += len;
		}
		input[i] = line;
		i++;
	}
	input[i] = NULL;
	return (input);
}

