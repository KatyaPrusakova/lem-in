# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 10:12:45 by ksuomala          #+#    #+#              #
#    Updated: 2021/06/04 16:43:46 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS = lemin.c \
	malloc_and_free.c \
	parse_input.c \
	parse_ants.c \
	parse_link.c \
	parse_room.c \
	create_queue.c \
	print_out.c \
	path_finding.c \
	path_calculations.c \
	bfs.c \
	save_path.c \
	test_dprint.c \
	visualize.c \
	edge_weight.c \
	move_ants.c \
	create_graph.c \
	link_exists.c

SRCS_DIR = src/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

OBJ_DIR = obj/

LIBFT = libft/libft.a

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

LINKS = -L libft -lft

INCL = -I includes -I libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LINKS)
	@echo "executable compiled!"

$(OBJS): $(LIBFT) $(addprefix $(SRCS_DIR), $(SRCS)) $(OBJ_DIR)
	@echo "Compiling..."
	@$(CC) $(FLAGS) -c $(addprefix $(SRCS_DIR), $(SRCS)) $(INCL)
	@echo "Compiled. Moving .o files..."
	@mv $(SRCS:.c=.o) $(OBJ_DIR)

$(LIBFT):
	@make -s -C libft

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	@make -s -C libft clean
	@rm -f $(OBJS)
	@echo "*.o removed!"

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME)
	@echo "Targets removed!"

re: fclean all
