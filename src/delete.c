// int				bfs(t_graph* data, int start_i)
// {
// 	t_queue		*q;
// 	t_room		*tmp;

// 	q = create_queue(data->room_count, data->q);
// 	print_queue(q, 0);
// 	tmp = data->adlist[start_i];
// 	tmp->visited = 1;
	
// 	// while didn't reach all nodes
// 		add_to_queue(q, tmp);
// 	print_queue(q, 0);
	
// 	// while (!queue_is_empty)
// 	// {
// 	// 	start_i = find_index_name_room(data, tmp->name);
// 	// 	printf("index of room %d\n", start_i);
// 	// 	add_to_queue(q, start_i);
// 	// 	tmp = tmp->next;
// 	// }
// 	return (1);
// }

// t_queue	*create_queue(int size, t_queue *new)
// {
// 	t_queue	*tmp;
// 	t_queue	*head;
// 	new = ft_memalloc(sizeof(t_queue));
// 	head = new;
// 	while (size--)
// 	{
// 		tmp = ft_memalloc(sizeof(t_queue));
// 		//new->index = 1;
// 		new->next = tmp;
// 		new = new->next;
// 	}
// //	printf("new->index %d\n", head->index);
// 	return (head);
// }

// Adding elements into queue
// void			add_to_queue(t_queue *q, t_room	*room)
// {
// 	q->name = room->name;
// 	if (room->next) // && not in queue already
// 	{
// 		//
// 		while (room->next)
// 		{
// 			q = q->next;
// 			room = room->next;
// 			q->name = room->name;
// 		}
// 	}
// //	printf("q->i %d\n", q->i);
// }

// void			print_queue(t_queue *q, int i)
// {
// 	while (q->next)
// 	{
// 		printf("queue note number %d q->name %s\n", i, q->name);
// 		q = q->next;
// 		i++;
// 	}
// }

// void			remove_from_queue(t_queue *q, int room_number)
// {
// 	q->index = q->index;
// 	//remove link from linked list
// }

// int				queue_is_empty(t_queue *q)
// {
// 	if (q->next == NULL)
// 		return (1);
// 	return (0);
// }


// t_graph*		parse_graph(char **av, t_graph* graph) 
// {
// 	int			i;
// 	i = 0;
// 	av[1] = NULL; // delete
// 	if (!(graph = create_graph(4))) // diffferent order, graph shall be created after input is read
// 		ft_error(graph, 2);
// 	if (ft_ants_num(graph))
// 		ft_printf("%d\n", graph->ants);
// 	while (get_next_line(0, &graph->line) == 1)
// 	{
// 		if (graph->line[0] == '#')
// 			ft_comment(graph);
// 		else if (ft_strchr(graph->line, ' ') && !(ft_strchr(graph->line, '-')) && !(ft_strchr(graph->line, '#')))
// 			ft_room(graph);
// 		else if (ft_strchr(graph->line, '-') && ft_link(graph))
// 			ft_printf("%s\n", graph->line);
// 		else
// 			ft_error(graph, 1);
// 		free(graph->line);
// 		graph->line = NULL;
// 	}
// 	ft_printf("\n");
// 	print_rooms(graph);
// 	bfs(graph, 1);
// 	return (0);
// }
