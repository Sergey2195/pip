# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/15 12:19:11 by iannmari          #+#    #+#              #
#    Updated: 2022/01/15 12:19:13 by iannmari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = pipex

SRCS	=	main.c ft_split.c ft_strjoin.c ft_strlen.c ft_strnstr.c pipex_utils.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

HEADER = pipex.h

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY	:	all clean fclean re

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(OBJS) $(NAME)

re		:	fclean all