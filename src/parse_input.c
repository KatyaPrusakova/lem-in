/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/05/28 14:26:55 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	**input_realloc(char **input, int len)
{
	char	**tmp;

	tmp = ft_memalloc(sizeof(char *) * (len * 2 + 1));
	tmp = ft_memcpy(tmp, input, sizeof(char *) * len);
	free(input);
	return (tmp);
}

/*
** Checking that all lines start with a #, or contain a ' ' or a '-' character.
*/

void	valid_map(char **input)
{
	int		i;

	i = 0;
	while (input[i] && (input[i][0] == '#' || ft_isnumeric_str(input[i])))
		i++;
	while (input[i] && (input[i][0] == '#' || ft_strchr(input[i], ' ')))
		i++;
	while (input[i] && (input[i][0] == '#' || ft_strchr(input[i], '-')))
		i++;
	if (input[i])
		print_error(10, input);
}

/*
** Saving the input as a 2-dimensional char array.
*/

char	**parse_input(void)
{
	int		i;
	int		len;
	char	*line;
	char	**input;

	i = 0;
	len = 10000;
	input = ft_memalloc(sizeof(char *) * len + 1);
	while (get_next_line(0, &line))
	{
		if (i == len)
		{
			input = input_realloc(input, len);
			len += len;
		}
		input[i] = line;
		i++;
	}
	if (i < 5)
		print_error(1, input);
	valid_map(input);
	return (input);
}
