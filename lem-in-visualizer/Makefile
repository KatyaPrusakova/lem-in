# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:21:02 by ksuomala          #+#    #+#              #
#    Updated: 2021/02/16 10:27:40 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

SRCS = visual_main.c \
save_graph.c \
backround.c \
ants.c \
animation.c \
draw_algorithm.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

C_FLAGS = -g -Wall -Wextra -Werror `sdl2-config --cflags`

L_FLAGS = `sdl2-config --libs`

LINKS = -L ../libft -lft -lSDL2_image -lSDL2_ttf -lm

INCL = -I ../includes -I ../libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(L_FLAGS) $(INCL) $(LINKS)
	@echo "executable compiled!"

$(OBJS): $(SRCS)
	@echo "Compiling..."
	$(CC) $(C_FLAGS) $(INCL) -c $(SRCS)
	@echo "*object files created"

clean:
	@rm -f $(OBJS)
	@echo "*.o removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "Targets removed!"

re: fclean all
