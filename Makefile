# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 10:33:39 by otuyishi          #+#    #+#              #
#    Updated: 2023/10/04 09:55:01 by otuyishi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc
CFLAGS := -Wextra -Wall -Werror #-g -fsanitize=address
# LDFLAGS := -fsanitize=address

SRCS := main.c pipex.c ft_split.c libft.c ft_utils.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
