# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/08 15:32:01 by cde-moul          #+#    #+#              #
#    Updated: 2019/06/06 15:08:29 by cde-moul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ft_ls

SRCSDIR			=	srcs

OBJSDIR			=	objs

SRCS			=	main.c \
					init.c \
					get_arg.c \
					error.c \
					sort.c \
					treat.c \
					long.c \
					long_2.c \
					long_3.c \
					long_4.c \
					longdev.c \
					struct.c \
					long2.c \
					algo.c \
					algo2.c \
					sort2.c \
					sort3.c \
					recursive.c \
					bonus.c

OBJS			=	$(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

CC				=	gcc -g

FLAG			=	-Wall -Wextra -Werror

INC				=	-I	libft/ -I includes/ -I libft/libft/

MY_LIB			=	libft/libft.a

HEADER			=	includes/ft_ls.h

LIB				=	-L libft -lft

RM				=	rm -rf

all				:	libft $(NAME)

$(NAME)			:	$(OBJS) $(MY_LIB)
					$(CC) $(FLAG) $(INC) $(OBJS)  -o $(NAME) $(LIB)

libft			:
					make -C libft/

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c $(HEADER)
					mkdir -p $(OBJSDIR)
					$(CC) -c $(FLAG) $(INC) $< -o $@

clean			:
					$(RM) $(OBJS)
					make -C libft/ clean

fclean			:	clean
					$(RM) $(NAME)
					$(RM) $(OBJSDIR)
					make -C libft/ fclean

re				:
					make fclean
					make all

.PHONY			:	libft clean re fclean
