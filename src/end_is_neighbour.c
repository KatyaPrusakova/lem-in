#include "lemin.h"

int	end_is_neighbour(t_room *list, int end)
{
	while (list)
	{
		if (list->index == end)
			return (1);
		list = list->next;
	}
	return (0);
}
