# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 10:33:39 by otuyishi          #+#    #+#              #
#    Updated: 2023/09/04 10:35:45 by otuyishi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol

CFLAGS := -Wextra -Wall -Werror -g -fsanitize=address


SRCS := pipex.c

OBJS := $(SRCS:.c=.o) 

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
