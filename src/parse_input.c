/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/03/02 23:25:10 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	**ft_realloc(char **input, int len)
{
	char **tmp;

	tmp = ft_memalloc(sizeof(char*) * (len * 2 + 1));
	tmp = ft_memcpy(tmp, input, sizeof(char*) * len);
	free(input);
	return(tmp);
}

void	valid_map(char **input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i][0] == '#' || ft_strisdigit(input[i]))
			i++;
		else
			break;
	}
	while (input[i])
	{
		if (input[i][0] == '#' || ft_strchr(input[i], ' '))
			i++;
		else
			break;
	}
	while (input[i])
	{
		if (input[i][0] == '#' || ft_strchr(input[i], '-'))
			i++;
		else
			break;
	}
	if (input[i])
		print_error(10, input);
}

char		**parse_input(void)
{
	int i;
	int len;
	char *line;
	char **input;

	i = 0;
	len = 10000;
	input = ft_memalloc(sizeof(char*) * len + 1);
	while (get_next_line(fd_zero, &line))
	{
		if (i == len)
			{
			input = ft_realloc(input, len);
			len += len;
		}
		input[i] = line;
		i++;
	}
	if (i < 5)  // file should have at least 6 lines
		print_error(1, input);
	valid_map(input);
	return (input);
}