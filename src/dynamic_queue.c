#include "lemin.h"

void	realloc_queue(t_queue *q)
{
	int *tmp;

	tmp = ft_memalloc(sizeof(int) * q->size * 2);
	if (!tmp)
		print_error(2, NULL);
	ft_memcpy(tmp, q->data, sizeof(int) * q->size);
	q->size *= 2;
	ft_memdel((void**)&q->data);
	q->data = tmp;
}

t_queue *init_queue(int size)
{
    t_queue *q;

    q = ft_memalloc(sizeof(t_queue));
	if (!q)
		print_error(2, NULL);
    q->data = ft_memalloc(sizeof(int) * size);
	if (!q->data)
		print_error(2, NULL);
    q->head = 1;
    q->size = size;
	q->len = 0;
    return (q);
}

void free_queue(t_queue *q)
{
	ft_memdel((void**)&q->data);
	ft_memdel((void**)&q);
}

void dequeue(t_queue *q)
{
	q->head++;
	q->len--;
}

t_queue *enqueue(int index, t_queue *q)
{
	if (!q)
		q = init_queue(10);
	if (!q)
		print_error(2, NULL);
	if (q->size <= q->head + q->len)
		realloc_queue(q);
	q->data[q->head + q->len] = index;
	q->len++;
	return (q);
}
