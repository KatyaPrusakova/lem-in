#include "lemin.h"

int	link_exists(t_graph *g, int a, int b)
{
	t_room	*tmp;

	tmp = g->adlist[a]->next;
	while (tmp)
	{
		if (tmp->index == b)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
