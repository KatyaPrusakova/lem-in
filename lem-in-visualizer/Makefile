# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:21:02 by ksuomala          #+#    #+#              #
#    Updated: 2021/02/23 00:25:09 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

SRCS = visual_main.c \
save_graph.c \
backround.c \
ants.c \
animation.c \
draw_algorithm.c

LIBSDL2 = lib/libSDL2/lib/libSDL2.a

LIBSDL_MAKE = libSDL2/Makefile

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

C_FLAGS = -g -Wall -Wextra -Werror `$(lib_dir)libSDL2/bin/sdl2-config --cflags`

L_FLAGS = `$(lib_dir)libSDL2/bin/sdl2-config --libs`

LINKS = -L ../libft -lft

INCL = -I ../includes -I ../libft -I libSDL2/include

lib_dir = lib/

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(L_FLAGS) $(INCL) $(LINKS)
	@echo "executable compiled!"

$(OBJS): $(SRCS) $(LIBSDL2) | $(lib_dir)
	@echo "Compiling..."
	$(CC) $(C_FLAGS) $(INCL) -c $(SRCS)
	@echo "*object files created"

clean:
	@rm -f $(OBJS)
	@echo "*.o removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=libSDL2 clean; fi

fclean: clean
	@rm -f $(NAME)
	@echo "Targets removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=libSDL2 distclean; fi
	rm -rf $(lib_dir)



$(LIBSDL2): $(lib_dir)
	cd libSDL2 && ./configure --prefix=$(abspath $(lib_dir)libSDL2) --disable-shared --disable-video-wayland
	$(MAKE) --directory=libSDL2
	$(MAKE) --directory=libSDL2 install

$(lib_dir):
	mkdir $(@)

re: fclean all
