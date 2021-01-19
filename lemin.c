/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:05 by eprusako          #+#    #+#             */
/*   Updated: 2021/01/19 17:18:28 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

t_room* create_room( t_graph *, int a, int b) 
{
	
}

t_graph* create_graph(int rooms) 
{
	t_graph* new;

	new = ft_memalloc(sizeof(t_graph));
	new->room_count = rooms;
	new->adlist = ft_memalloc(sizeof(t_room*) * rooms);
	return (new);
}

int	ft_islink(char *s)
{
	if (ft_strchr(s, '-'))
		return (1);
	return (0);
}

int	ft_isroom(char *s)
{
	if (ft_strchr(s, ' ') && ft_isdigit(s[0]))
		return (1);
	return (0);
}

char	*ft_spacetrim(char const *s)
{
	size_t	i;
	size_t	l;
	char	*ptr;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '\0')
		return (0);
	ptr = ft_strnew(i + 1);
	if (!ptr)
		return (NULL);
	while (l <= i)
	{
		ptr[l] = s[l];
		l++;
	}
	return (ptr);
}

t_graph* parse_graph(t_graph* graph) 
{
	char	**line;
	char	**info;
	int		i;

	i = 0;
	//read input
	get_next_line(0, line);
	graph->ants = ft_atoi(line);
	free(line);

	while (0 < get_next_line(0, line))
	{
		info =
	}

	if (ft_isroom(line))
		{
			graph->adlist[i]->name = ft_spacetrim(line);
			i++;
		}
//	if (ft_islink(line))
			
	// create_graph();
}

int main(void)
{
	t_graph* data;

	parse_graph(data);
}