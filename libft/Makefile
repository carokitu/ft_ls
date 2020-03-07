# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/07 14:42:46 by cde-moul          #+#    #+#              #
#    Updated: 2019/06/04 14:14:28 by cde-moul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = treat.c init.c conv.c conv2.c noconv.c   \
	   convdec.c conv_base.c double.c largeur.c \
	   precision.c double_to_char.c largeur_float.c \
	   precision_double.c precision_base.c bonus.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

INC = -I libft

LIB = libft/libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	cp $(LIB) $(NAME)
	ar -rc $(NAME) $(OBJS) $(LIB)
	ranlib $(NAME)

%.o		:	%.c libftprintf.h
	gcc -g -c $(FLAGS) $< -o $@ $(INC)

clean :
	rm -rf $(OBJS)
	make clean -C ./libft

fclean : clean
	rm -rf $(NAME)
	rm -rf ./libft/libft.a

re	: 
	make fclean
	make all
