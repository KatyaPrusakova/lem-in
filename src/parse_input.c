/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/02/15 15:58:03 by ksuomala         ###   ########.fr       */
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

// int		ft_arraylen(char **s)
// {
// 	int		i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 		i++;
// 	return (i);
// }

char		**parse_input(void)
{
	int i;
	int len;
	char *line;
	char **input;

	i = 0;
	len = 5;
	input = ft_memalloc(sizeof(char*) * len + 1);
	while (get_next_line(0, &line) == 1)
	{
		ft_printf("%s\n", line);
		if (i == (len - 1))
		{
			input = ft_realloc(input, len);
			len += len;
		}
		input[i] = line;
		i++;
	}
	ft_n(1);
	// if (len == 5)  // file should have at least 6 lines
	// 	print_error(1);
	return (input);
}

