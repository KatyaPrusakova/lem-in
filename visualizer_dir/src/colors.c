#include "lemin_visual.h"

/*
** If the color values of a and b are the same, return 0. Else return 1.
*/

int	rgba_cmp(t_rgb a, t_rgb b)
{
	if (a.a == b.a
		&& a.r == b.r
		&& a.g == b.g
		&& a.b == b.b)
		return (0);
	else
		return (1);
}

void	set_edge_color(t_edge *links, int a, int b, t_rgb color)
{
	while (links)
	{
		if ((links->src == a && links->dst == b)
			|| (links->src == b && links->dst == a))
		{
			links->rgba = color;
			return ;
		}
		links = links->next;
	}
}

void	edge_colors(t_edge *edges)
{
	while (edges)
	{
		if (edges->weight)
		{
			if (edges->weight == 1)
				edges->rgba = RGBA_REVERSED;
			else if (edges->weight == 2)
				edges->rgba = RGBA_REMOVED;
			else if (edges->weight == 3)
				edges->rgba = RGBA_PATH;
		}
		else
			edges->rgba = RGBA_VOID;
		edges = edges->next;
	}
}
