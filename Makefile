# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/22 12:49:02 by eprusako          #+#    #+#              #
#    Updated: 2021/01/22 13:05:11 by eprusako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			lem-in

LIBFT = ./libft/
DIR_SRC = src
HEADER = -I includes/
SRC = lemin.c

YELLOW = "\033[1;33m"
NOCOLOR = "\033[0m"

SRCS = $(addprefix $(DIR_SRC)/, $(SRC))
OBJS=$(notdir $(SRCS:.c=.o))

all: $(NAME)

$(NAME):
	@echo $(YELLOW)Compiling LEM-IN...$(NOCOLOR)
	@make -C $(LIBFT)
	@gcc -g -Wall -Wextra -Werror -c $(SRCS) $(HEADER)
	@gcc -g $(HEADER) $(OBJS) libft/libft.a -o $(NAME)

clean:
	@echo $(YELLOW)Cleaning...$(NOCOLOR)
	@/bin/rm -rf $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@echo $(YELLOW)F-cleaning...$(NOCOLOR)
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: all clean

.PHONY: $(NAME), all, clean, fclean, re